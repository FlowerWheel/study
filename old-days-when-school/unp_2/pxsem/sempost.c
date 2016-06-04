#include "lueap.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
	sem_t	*sem;
	int		val;

	if (argc != 2)
		err_quit("usage : semwait <name>");

	if ((sem = sem_open(argv[1], 0)) == SEM_FAILED)
		err_sys("sem_open error");

	if (sem_post(sem) == -1)
		err_sys("sem_wait error");

	if (sem_getvalue(sem, &val) == -1)
		err_sys("sem_getvalue error");
	printf("value = %d\n", val);

	if (sem_close(sem) == -1)
		err_sys("sem_close error");

	pause();
	
	return 0;
}
