#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define M 100
#undef _DEBUG
int do_with_fd(int fd) {
	int count = 0;
	char buf[20];
	while (1) {
		count = read(fd, buf, 20);
		// This indicates a fin of the connection has arrived.
		if (count == 0) {
#ifdef _DEBUG
			fprintf(stdout, "Zero buf\n");
#endif
			break;
		}
		// This indicates *no more* buffers can be read from fd.
		if (count == -1 && errno == EAGAIN) {
#ifdef _DEBUG
			fprintf(stdout, "-1 buf\n");
#endif
			break;
		}
		fprintf(stdout, "%s length:%d\n", buf,count);
	}
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
			if (evnts[i].events & EPOLLERR||
				evnts[i].events & EPOLLHUP||
				(!(evnts[i].events & EPOLLIN))) {
				fprintf(stdout,"epoll error events:=%u\n", evnts[i].events);
				close(evnts[i].data.fd);
				continue;
			}
			if (evnts[i].data.fd == fd) {
				fd_in = accept(fd, (struct sockaddr*)&sock_in, &size);
				if (fd_in != -1) {
					fcntl(fd_in, F_SETFL, fcntl(fd_in, F_GETFL) | O_NONBLOCK);
					// prevents multiple invoke by OR EPOLLONESHOT
					ev.events = EPOLLET|EPOLLIN;
					ev.data.fd = fd_in;
					epoll_ctl(fde, EPOLL_CTL_ADD, fd_in, &ev);
				}
			} else {
#ifdef _DEBUG
				fprintf(stdout, "Events %d,fd%d: ", evnts[i].events,evnts[i].data.fd);
#endif
				do_with_fd(evnts[i].data.fd);
			}
		}
	}
	return 0;
}
