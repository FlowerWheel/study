#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

//extern char *optarg;
//extern int	optind, opterr, optopt;

#define FILEMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP 

int main (int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while((c = getopt(argc, argv, "e")) != -1)
		switch(c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
		}

	if (optind != argc - 1)
	{
		perror("usage : mqcreate [-e] <name>");
		exit(EXIT_FAILURE);
	}
	puts("*****************************\n");
	mqd = mq_open(argv[optind], flags/*, FILEMODE, NULL*/);
	mq_close(mqd);
	return 0;
}
