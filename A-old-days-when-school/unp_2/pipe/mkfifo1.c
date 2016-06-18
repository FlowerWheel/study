#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define SERV_TO_CLI "/tmp/serv_to_cli.fifo"
#define CLI_TO_SERV "/tmp/cli_to_serv.fifo"

int main (void)
{
	pid_t	pid;
	int		fd1, fd2;

	if (mkfifo(SERV_TO_CLI, O_RDWR) == -1)
	{
		perror("mkfifo error ");
		exit(EXIT_FAILURE);
	}
	if (mkfifo(CLI_TO_SERV, O_RDWR) == -1)
	{
		perror("mkfifo error ");
		exit(EXIT_FAILURE);
	}

	if ((fd1 = open(SERV_TO_CLI, O_RDWR)) == -1)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
	if ((fd2 = open(CLI_TO_SERV, O_RDWR)) == -1)
	{
		perror("open error");
		close(fd1);
		exit(EXIT_FAILURE);
	}

	if ((pid = fork()) == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{

	}
	else
	{

	}

	return 0;
}
