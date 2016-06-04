#include "lueap.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	sem_t		*sem;
	int			val;

	if (argc != 2)
		err_quit("usage : %s <name>", argv[0]);
	
	if ((sem = sem_open(argv[1], 0)) == SEM_FAILED)
		err_sys("sem_open error");

	sem_getvalue(sem, &val);
	printf("value = %d\n", val);

	return 0;
}
