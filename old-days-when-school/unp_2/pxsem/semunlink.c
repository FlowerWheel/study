#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

int main (int argc, char **argv)
{
	if (argc != 2)
		err_quit("usage : %s <name>", argv[0]);

	if (sem_unlink(argv[1]) == -1)
		err_sys("sem_unlink error");

	return 0;
}
