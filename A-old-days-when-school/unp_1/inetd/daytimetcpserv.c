#include "myunp.h"
#include <time.h>

int main (int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t addrlen, len;
	struct sockaddr *cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	if (argc < 2 || argc >3)
		err_quit("usage : %s [ <host> ] <service|port>");

	daemon_init(argv[0], 0);

	if (argc == 2)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else 
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);

	cliaddr = Malloc(addrlen);

	while(1)
	{
		len = addrlen;
		connfd = Accept(listenfd, cliaddr, &len);
//		err_msg("connection from %s", sock_ntop(cliaddr, len));
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(connfd, buff, strlen(buff));
		Close(connfd);
	}
	return 0;
}
