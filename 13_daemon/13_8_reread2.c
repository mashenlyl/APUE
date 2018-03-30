#include "apue.h"
#include <syslog.h>
#include <errno.h>

extern int	already_running(void);
extern int	lockfile(int);

void
reread(void)
{
	/* ... */
}

void
sigterm(int signo)
{
	syslog(LOG_INFO, "got SIGTERM; exiting");
	exit(0);
}

void
sighup(int signo)
{
	syslog(LOG_INFO, "Re-reading configuration file");
	reread();
}

int
main(int argc, char *argv[])
{
	char 		*cmd;
	struct sigaction sa;
	sigset_t	zeromask;

	if ((cmd = strrchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;
	
	/*
	 * Become a daemon.
	 */
	daemonize(cmd);

	/* 
	 * Make sure only one copy of the daemon is running.
	 */
	if (already_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	/*
	 * Handle signals of interest.
	 */
	sigemptyset(&zeromask);
	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = 0;
	if (sigaction(SIGTERM, &sa, NULL) < 0) {
		syslog(LOG_ERR, "can't catch SIGTERM: %s", strerror(errno));
		exit(1);
	}

	sa.sa_handler = sigterm;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0) {
		syslog(LOG_ERR, "can't catch SIGHUP: %s", strerror(errno));
		exit(1);
	}

	/*
	 * Proceed with the rest of the daemon.
	 */
	if (sigsuspend(&zeromask) != -1) {
		syslog(LOG_ERR, "sigsuspend error: %s", strerror(errno));
		exit(1);
	}
	/* ... */
	exit(0);
}
