#include "myunp.h"
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int		n, on = 1;
	int		listenfd, connfd;
	char	buff[100];

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], NULL);
	else 
		err_quit("usage: tcprecvoob01 [<host>] <port#>");

	Setsockopt(listenfd, SOL_SOCKET, SO_OOBINLINE, &on, sizeof(on));

	connfd = Accept(listenfd, NULL, NULL);

	sleep(2);
	while (1)
	{
		if (Sockatmask(connfd))
			printf("At OOB Mark\n");

		if ((n = Read(connfd, buff, sizeof(buff) - 1)) == 0)
		{
			printf("received EOF\n");
			exit(0);
		}
		buff[n] = 0;
		printf("read %d normal bytes : %s\n", n, buff);
	}
	return 0;	
}
