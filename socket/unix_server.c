#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

int keeprunning = 1;
void intsig_process(int dummy) {
	keeprunning = 0;
}

int main()
{
	struct sockaddr_un *sock = malloc(sizeof(struct sockaddr_un)),
					   *sock_in = malloc(sizeof(struct sockaddr_un));
	char path[] = ".sock";
	int fd = -1, fd_in = -1;
	unsigned int client_size = 0;
	int size = 0;
	char *buf = malloc(1000);
	struct sigaction sa = {
		.sa_handler = intsig_process,
		.sa_mask = {0},
		.sa_flags = 0,
	};

	sigaction(SIGINT, &sa, NULL);

	// Since POSIX standard has AF_UNIX but not AF_LOCAL.
	sock->sun_family = AF_UNIX;
	strncpy(sock->sun_path, path, strlen(path)+1);
	client_size = sizeof(*sock_in);
	// set the socket NON-BLOCKING so non-block in
	// read/write/accpet.
	fd = socket(AF_UNIX, SOCK_STREAM|SOCK_NONBLOCK, 0);
	bind(fd, (struct sockaddr *)sock, sizeof(*sock));
	if (errno == 98) {
		perror("Session file exists.");
		exit(1);
	}
	else if (errno == 111) {
		perror("Connection refuses.");
		exit(1);
	}
	listen(fd, SOMAXCONN);
	do {
		fd_in = accept(fd, (struct sockaddr*)sock_in, &client_size);
	
		while (-1 !=  fd_in && keeprunning) {
			size = read(fd_in, buf, 1000);
			if (!size) {
				close(fd_in);
				break;
			}
			fprintf(stdout, "Connection from: %s\n", sock_in->sun_path);
			fprintf(stdout, "Bytes received: %u\n", size);
			fprintf(stdout, "Text: %s\n", buf);
		}
	} while (keeprunning && strncmp("Quit.", buf, 5));
	// deletes socket file
	unlink(path);
	return 0;
}
