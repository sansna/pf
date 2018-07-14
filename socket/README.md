Socket programming
=
socket server: 
```
fd = socket(AF_XXX, SOCK_STREAM|SOCK_DGRAM, 0);
bind(fd, sockaddr, sizeof(*sockaddr));
listen(fd, SOMAXCONN);
// If reside within while loop, it is blocked
// no matter the socket is set as SOCK_NONBLOCK or not;
// otherwise if not set SOCK_NONBLOCK, accept is blocked;
// if set SOCK_NONBLOCK and if accpet detects no incoming
// connection, retval is -1.
// Note: errno is set to EAGAIN no matter accpet detects
// incoming connection or not.
fd_in = accept(fd, sockaddr_cli, &sockaddr_cli_size);
read(fd_in, buf, sizeofbuf);
close(fd_in);
//unlink(); // in AF_UNIX mode
```
socket client:
```
fd = socket(AF_XXX, SOCK_STREAM|SOCK_DGRAM, 0);
connect(fd, sockaddr_ser, sizeof(sockaddr_ser));
write(fd, buf, sizeofbuf);
close(fd);
```
