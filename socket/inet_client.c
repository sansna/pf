#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/ip.h>

int main()
{
	struct sockaddr_in *sock = malloc(sizeof(struct sockaddr_in));
	int fd = -1;
	char str[] = "Hello world!";

	fd = socket(AF_INET, SOCK_STREAM, 0);
	sock->sin_addr.s_addr = inet_addr("127.0.0.1");
	sock->sin_port = htons(7777);
	sock->sin_family = AF_INET;

	connect(fd, (struct sockaddr *)sock, sizeof(*sock));
	write(fd, str, 12);
	close(fd);
	return 0;
}
