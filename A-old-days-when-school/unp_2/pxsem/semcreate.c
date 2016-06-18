#include "lueap.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)


int main (int argc, char **argv)
{
	int			c, flags;
	sem_t		*sem;
	unsigned	value;

	flags = O_RDWR | O_CREAT;
	value = 1;

	while ((c = getopt(argc, argv, "ei:")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
			case 'i':
				value = atoi(optarg);
				break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage : %s [-e] [-i value] <name>", argv[0]);

	sem = sem_open(argv[optind], flags, FILE_MODE, value);
	if (sem == SEM_FAILED)
		err_sys("sem_open");
	sem_close(sem);

	return 0;
}
