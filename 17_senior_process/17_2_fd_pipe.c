#include "apue.h"
#include <sys/socket.h>

/*
 * Return a full-duplex pupe (a UNIX domain socket) with
 * the two file descriptors returned in fd[0] and fd[1]
 */
int
fd_pipe(int fd[2])
{
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
