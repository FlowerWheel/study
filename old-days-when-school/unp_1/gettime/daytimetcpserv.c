#include "myunp.h"

int main (int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t len;
	char buff[MAXLINE];
	time_t ticks;
	struct sockaddr_storage cliaddr;

	if (argc != 2)
		err_quit("usage : %s <service/port#>", argv[0]);

	listenfd = tcp_listen(NULL, argv[1], NULL);

	while(1)
	{
		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &len);

		ticks = time(NULL);

		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff, strlen(buff));
	}
	exit (EXIT_SUCCESS);
}
