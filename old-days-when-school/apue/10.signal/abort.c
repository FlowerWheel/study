#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void abort(void)
{
	sigset_t			mask;
	struct sigaction	action;

	sigaction(SIGABRT, NULL, &action);
	if ( action.sa_handler == SIG_IGN )
	{
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if ( action.sa_handler == SIG_DFL )
		fflush(NULL);

	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);

	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);

	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);

	exit(1);
}

int main(void)
{
	return 0;
}