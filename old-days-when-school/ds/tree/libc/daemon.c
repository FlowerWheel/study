#include "lueap.h"
#include  <syslog.h>

#define MAXFD 64

extern int daemon_proc;

int daemon_init(const char *pname, int facility)
{
	int i;
	pid_t pid;

	if ((pid = Fork()) < 0)
		return -1;
	else if (pid)
		_exit(0);

	if (setsid() < 0)
		return -1;

	Signal(SIGHUP, SIG_IGN);

	if ((pid = Fork()) < 0)
		return -1;
	else if (pid)
		_exit(0);

	daemon_proc = 1;

	chdir("/");

	for (i = 0; i < MAXFD; i++)
		close(i);

	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);
	return 0;
}

void daemon_inetd(const char *pname, int facility)
{
	daemon_proc = 1;
	openlog(pname, LOG_PID, facility);
}
