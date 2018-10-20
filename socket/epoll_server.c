#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>

#define M 100
int do_with_fd(int fd) {
	char buf[20];
	read(fd, buf, 20);
	//usleep(100);
	//write(fd, buf, strlen(buf));
	fprintf(stdout, "%s\n", buf);
	return 0;
}

int main() {
	struct sockaddr_in sock, sock_in;
	int fd, fd_in, fde = epoll_create(M);
	struct epoll_event ev, evnts[M+1];
	int i = 0;
	uint size;
	int nfds = 0;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	sock.sin_addr.s_addr = INADDR_ANY;
	sock.sin_family = AF_INET;
	sock.sin_port = htons(6666);
	bind(fd, (const struct sockaddr *)&sock, sizeof(struct sockaddr_in));
	listen(fd, SOMAXCONN);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	epoll_ctl(fde, EPOLL_CTL_ADD, fd, &ev);
	while (1) {
		nfds = epoll_wait(fde, evnts, M+1, 400);
		for (i = 0; i < nfds; i++) {
			if (evnts[i].data.fd == fd) {
				fd_in = accept(fd, (struct sockaddr*)&sock_in, &size);
				if (fd_in != -1) {
					fcntl(fd_in, F_SETFL, O_NONBLOCK);
					// prevents multiple invoke by EPOLLONESHOT
					ev.events = EPOLLET|EPOLLIN|EPOLLONESHOT;
					ev.data.fd = fd_in;
					epoll_ctl(fde, EPOLL_CTL_ADD, fd_in, &ev);
				}
			} else {
				do_with_fd(evnts[i].data.fd);
			}
		}
	}
	return 0;
}
