#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

int main (void)
{
	int		pipebuflen;
	int		pipefd[2];
	char	str[N] = "abcdefghijklmn";
	char	recv[N];

	if ((pipebuflen = pathconf("/", _PC_PIPE_BUF)) == -1)
	{
		perror("pathconf error");
		exit(EXIT_FAILURE);
	}
		
	printf("%d\n", pipebuflen);

	if (pipe(pipefd) == -1)
	{
		perror("piper error");
		exit(EXIT_FAILURE);
	}
	
	write(pipefd[1], str, strlen(str) + 1);

	printf("%d\n", sizeof(str));
	printf("%d\n", strlen(str));

	read(pipefd[0], recv, N);

	printf("%d\n", strlen(recv));
	printf("%s\n", recv);

	return 0;
}
