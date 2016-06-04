#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define PAGER "${PAGER: -more}"
#define MAXLINE 1024

int main (int argc, char **argv)
{
	char	line[MAXLINE];
	FILE	*fpin, *fpout;

	if (argc != 2)
	{
		perror("usage : popen1 <pathname>");
		exit(EXIT_FAILURE);
	}

	if ((fpin = fopen (argv[1], "r")) == NULL)
	{
		perror("fopen error");
		exit(EXIT_FAILURE);
	}

	if ((fpout = popen ("/bin/more", "w")) == NULL)
	{
		perror("popen error");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, MAXLINE, fpin) != NULL)
	{
		if (fputs(line, fpout) == EOF)
		{
			perror("fputs error to pipe");
			exit(EXIT_FAILURE);
		}
	}
	if (ferror(fpin))
	{
		perror("ferror error");
		exit(EXIT_FAILURE);
	}
	if (pclose(fpout) == -1)
	{
		perror("pclose error");
		exit(EXIT_FAILURE);
	}
	return 0;
}
