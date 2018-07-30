#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include <sys/socket.h> //see man 7 socket
//#include <netinet/in.h>

#include <netinet/ip.h> //see man 7 ip
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in *sock_ser = malloc(sizeof(struct sockaddr_in)),
					   *sock_in = malloc(sizeof(struct sockaddr_in));
	int fd = -1, fd_in = -1;
	int bytes = 0;
	unsigned int size = sizeof(*sock_in);
	char *buf = malloc(sizeof(1000));
	sock_ser->sin_family = AF_INET;
	sock_ser->sin_port = htons(7777);
	sock_ser->sin_addr.s_addr = INADDR_ANY;

	if (-1 == (fd = socket( AF_INET, SOCK_STREAM, 0 )))
		perror("Socket fd -1");
	if (bind(fd, (const struct sockaddr *)sock_ser, sizeof(struct sockaddr)))
		return -1;

recon:
	listen(fd, SOMAXCONN);
	fd_in = accept(fd, (struct sockaddr *)sock_in, &size);

	fprintf(stdout, "Client connected: %s:%u\n", inet_ntoa(sock_in->sin_addr),
			ntohs(sock_in->sin_port));

	while (1) {
		bytes = read(fd_in, (void *)buf, 1000);
		if (bytes <= 0) {
			close(fd_in);
			goto recon;
		}
		fprintf(stdout, "Bytes received: %u\n", bytes);
		fprintf(stdout, "Text: %s\n", buf);
	}
	return 0;
}
