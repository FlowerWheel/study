#include "myunp.h"

#define		PORT	6789


int main (int argc, char **argv)
{
	int			listenfd, connfd, udpfd, nready, maxfdp1;
	struct sockaddr_in	servaddr, cliaddr;
	fd_set		rset;
	socklen_t	len;
	ssize_t		n;
	const int	on = 1;
	char		mesg[MAXLINE];
	pid_t		childpid;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family		=	AF_INET;
	servaddr.sin_port		=	htons(PORT);
	servaddr.sin_addr.s_addr=	htonl(INADDR_ANY);
//	if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) < 0)
//		err_sys("inet_pton error");


	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		err_sys("setsockopt error");

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (listen(listenfd, LISTENQ) < 0)
		err_sys("listen error");

	if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family		=	AF_INET;
	servaddr.sin_port		=	htons(PORT);
	servaddr.sin_addr.s_addr=	htonl(INADDR_ANY);

	if (bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal error");
	
	maxfdp1 = listenfd >= udpfd ? listenfd + 1 : udpfd + 1;
	FD_ZERO(&rset);
	while (1)
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if ((nready = select (maxfdp1, &rset, NULL, NULL, NULL)) < 0)
		{
			if (errno == EINTR)
				continue;
			else 
				err_sys("select error");
		}
		
		if (FD_ISSET(listenfd, &rset))
		{
			len = sizeof(cliaddr);
			if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len)) < 0)
				err_sys("accept error");
			if ((childpid = fork ()) == 0)
			{
				close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			close(connfd);
		}
		if (FD_ISSET(udpfd, &rset))
		{
			len = sizeof(cliaddr);
			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
			Sendto(udpfd, mesg, n, 0, (struct sockaddr *)&cliaddr, len);
		}
	}
	return 0;
}
