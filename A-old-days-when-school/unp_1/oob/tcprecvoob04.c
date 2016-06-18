#include "myunp.h"

int main(int argc, char **argv)
{
	int		n, justrecvoob = 0;
	int		listenfd, connfd;
	char	buff[100];
	fd_set	rset, xset;

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], NULL);
	else 
		err_quit("usage: tcprecvoob01 [<host>] <port#>");

	connfd = Accept(listenfd, NULL, NULL);

	FD_ZERO(&rset);
	FD_ZERO(&xset);
	while (1)
	{
		FD_SET(connfd, &rset);
		if (justrecvoob == 0)
			FD_SET(connfd, &xset);
	
		select(connfd + 1, &rset, NULL, &xset, NULL);

		if (FD_ISSET(connfd, &xset))
		{
			n = Recv(connfd, buff, sizeof(buff) - 1, MSG_OOB);
			buff[n] = 0;
			printf("read %d OOB bytes : %s \n", n, buff);
			justrecvoob = 1;
			FD_CLR(connfd, &xset);
		}

		if (FD_ISSET(connfd, &rset))
		{
			if ((n = Read(connfd, buff, sizeof(buff) - 1)) == 0)
			{
				printf("received EOF\n");
				exit(0);
			}
			buff[n] = 0;
			printf("read %d normal bytes : %s\n", n, buff);
			justrecvoob = 0;
		}
	}
	return 0;	
}
