#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <mqueue.h>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage : mqunlink <mqname>\n");
		exit(EXIT_FAILURE);
	}
	if (mq_unlink(argv[1]) == -1)
	{
		perror("mq_unlink error");
		exit(EXIT_FAILURE);
	}
	return 0;
}
