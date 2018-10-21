#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define M 100
pthread_t tid[M];
void *pfunc(void *arg) {
	struct sockaddr_in sock;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		perror("socket");
	pthread_t ltid = pthread_self();
	int i = 0;
	char buf[20],buf2[20];
	int ret = 0;

	fcntl(fd, F_SETFL, O_NONBLOCK);
	inet_aton("127.0.0.1", &sock.sin_addr);
	sock.sin_family = AF_INET;
	sock.sin_port = htons(6666);
	connect(fd, (const struct sockaddr*)&sock, sizeof(struct sockaddr));
	for (i = 0; i < M; i ++) {
		if (tid[i] == ltid) {
			break;
		}
	}
	snprintf(buf, 20, "HelloWorld%d", i);
	write(fd, buf, strlen(buf));
	
	// receiving from server
	while (-1 == (ret = read(fd, buf2, 20)) && errno == EAGAIN)
		usleep(10000);
	fprintf(stdout,"%s\n", buf2);

	//fprintf(stdout,"%s\n", buf);

	//XXX: When you close the fd, a fin is sent over to server
	// and server side's epoll will prompt for EPOLLIN|EPOLLET event
	// causing the further read() of 0 byte.
	if (0 == (ret = read(fd, buf2, 20))) {
#ifdef _DEBUG
		fprintf(stdout, "received fin\n");
#endif
		close(fd);
	}
	return NULL;
}

int main() {
	int i = 0;
	for (;i < M; i++) {
		pthread_create(&tid[i], NULL, pfunc, NULL);
	}
	for (i = 0; i < M; i ++) {
		pthread_join(tid[i], NULL);
	}
	return 0;
}
