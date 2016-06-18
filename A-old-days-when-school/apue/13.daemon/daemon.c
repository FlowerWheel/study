#include	"lueap.h"
#include	<syslog.h>
#include	<fcntl.h>
#include	<sys/resource.h>

void daemonize(const  char *cmd)
{
	int		i, fd0, fd1, fd2;
	pid_t	pid;

	struct rlimit rl;
	struct sigaction sa;

	/*1*/
	umask(0); // Clear file creation mask.

	/*2*/
	if ((pid = fork()) < 0) // fork
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) // parent
		exit(0);

	/*Child*/
	/*3*/
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP");
	
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) // parent
		exit(0);

	/*Child's Child*/
	/*4*/
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /");

	/*5*/
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can't get file limit", cmd);
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; ++i)
		close(i);

	/*6*/
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 0 || fd2 != 0)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
	printf("*************************\n");

}

int main (void)
{
	daemonize("./sleep");

	return 0;
}
