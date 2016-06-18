#include "myunp.h"

int		listenfd, connfd;
void	sig_urg(int);

int main(int argc, char **argv)
{
	int		n;
	char	buff[100];

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], NULL);
	else 
		err_quit("usage: tcprecvoob01 [<host>] <port#>");

	connfd = Accept(listenfd, NULL, NULL);

	Signal(SIGURG, sig_urg);
	if (fcntl(connfd, F_SETOWN, getpid()) < 0)
		err_sys("fcntl error");
		/*if not have fcntl F_SETOWN, con not recv OOB data in this proc*/

	while (1)
	{
		if ((n = Read(connfd, buff, sizeof(buff) - 1)) == 0)
		{
			printf("recv EOF \n");
			exit(0);
		}
		buff[n] = 0;
		printf("read %d normal bytes : %s \n", n, buff);
	}
		
}

void sig_urg(int signo)
{
	int		n;
	char	buff[100];

	printf("SIGURG received\n");
	n = Recv(connfd, buff, sizeof(buff) - 1, MSG_OOB);
	buff[n] = 0;
	printf("read %d oob bytes : %s\n", n, buff);
}
