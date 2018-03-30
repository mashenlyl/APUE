#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (setsid() == getpid())
			printf("session success\n");
		if (open("/dev/tty", O_RDONLY | O_NOCTTY) < 0)
			err_sys("open error");
	}
	
	sleep(5);
	exit(0);
}

