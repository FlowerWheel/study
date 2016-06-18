#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "lueap.h"

static void sig_alrm1(int signo)
{

}
unsigned int sleep1(unsigned int nsecs)
{
	if ( signal(SIGALRM, sig_alrm1) == SIG_ERR )
		return nsecs;
	alarm(nsecs);
	// here have a time window
	pause();
	return alarm(0);
}


#include <setjmp.h>
static jmp_buf env_alrm;
static void sig_alrm2(int signo)
{
	longjmp(env_alrm, 1);
}
unsigned int sleep2(unsigned int nsecs)
{
	if ( signal(SIGALRM, sig_alrm2) == SIG_ERR )
		return nsecs;
	if ( setjmp(env_alrm) == 0)
	{
		alarm(nsecs);
		pause();
	}
	return alarm(0);
}

static void sig_alrm(int signo)
{
	/**/
}
unsigned int sleep(unsigned int nsecs)
{
	struct sigaction	newact, oldact;
	sigset_t			newmask, oldmask, suspmask;
	unsigned int		unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(nsecs);

	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);
	sigsuspend(&suspmask);

	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);

	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return (unslept);
}

static void sig_int(int signo)
{ 
	int			i, j;
	volatile int k;

	printf("\nsig_int starting\n");
	for (i = 0; i < 30; i++)
		for (j = 0; j < 40; j++)
			k += i * j;
	printf("sig_int finished k = %d\n", k);
}
int main (void)
{ 
	unsigned int	unslept;

	if ( signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);
	exit(0);
}
