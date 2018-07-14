#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/un.h>

int main()
{
	struct sockaddr_un *sock = malloc(sizeof(struct sockaddr_un));
	char path[] = ".sock";
	int fd = -1;
	sock->sun_family = AF_UNIX;
	strncpy(sock->sun_path, path, strlen(path)+1);
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr *)sock, sizeof(*sock));
	write(fd, "Hello world!\n\0", 14);
	close(fd);
	return 0;
}
