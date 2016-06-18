#include "myunp.h"

void Signal(int signum, sighandler_t sighandler)
{
	if (signal(signum, sighandler) == SIG_ERR)
		err_sys("signal error");
}

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
