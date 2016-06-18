#include "lueap.h"

void prsigmask(const char *str)
{ 
	sigset_t	sigset;
	int			errno_save;

	errno_save = errno;
	if ( sigprocmask(0, NULL, &sigset) < 0 )
		err_sys("sigprocmask error");
	printf("%s", str);

	if ( sigismember(&sigset, SIGINT) )
		printf("SIGINT ");
	if ( sigismember(&sigset, SIGQUIT) )
		printf("SIGQUIT ");
	if ( sigismember(&sigset, SIGUSR1) )
		printf("SIGUSR1 ");
	if ( sigismember(&sigset, SIGALRM) )
		printf("SIGALRM ");
	printf("\n");
	errno = errno_save;
}

static void sig_int(int signo)
{
	prsigmask("\nin sig_int : ");
}

int main (void)
{
	sigset_t	newmask, oldmask, waitmask;

	prsigmask("program start : ");

	if ( signal(SIGINT, sig_int) == SIG_ERR )
		err_sys("signal(SIGINT) error");

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if ( sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0 )
		err_sys("sigprocmask(SIG_BLOCK) error");

	prsigmask("in critical region : ");

	if ( sigsuspend(&waitmask) != -1 )
		err_sys("sigsuspend error");

	prsigmask("after return from sigsuspend : ");

	if ( sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0 )
		err_sys("sigprocmask(SIG_BLOCK) error");

	prsigmask("program exit : ");

	return 0;
}
