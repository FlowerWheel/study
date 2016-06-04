#include "myunp.h"

#define SERVPORT 6688 

int main (int argc, char **argv)
{
	struct sockaddr_in	servaddr, cliaddr;
	socklen_t	calen;
	fd_set	set, rset;
	ssize_t	nread;
	int		i, maxi, maxfd, nready;
	int		sockfd, connfd;
	int		client[FD_SETSIZE];
	char	buf[MAXLINE];

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	Listen(sockfd, 5);

	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	maxi = 0;
	maxfd = sockfd;	

	FD_ZERO(&set);
	FD_SET(sockfd, &set);

	while(1)
	{
		rset = set;
		if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) == -1)
			err_sys("select error");

		if (FD_ISSET(sockfd, &rset))
		{
			calen = sizeof(cliaddr);
			connfd = Accept(sockfd, (struct sockaddr*)&cliaddr, &calen);
			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] == -1)
				{
					client[i] = connfd;
					break;
				}
				printf("i = %d\n", i);
			if (i == FD_SETSIZE)
				err_quit("too many clients");
			FD_SET(connfd, &set);
			if (connfd > maxfd)
				maxfd = connfd;
			if (i > maxi)
				maxi = i;
			if (--nready <= 0)
				continue;
		}
		printf("maxi = %d\n", maxi);
		for (i = 0; i <= maxi; i++)
		{
			if (((connfd = client[i]) > 0) && FD_ISSET(connfd, &rset))
			{
				if ((nread = Read(connfd, buf, MAXLINE)) == 0)
				{
					if(maxi == connfd)
						maxi --;
					Close(connfd);
					FD_CLR(connfd, &set);
					client[i] = -1;
				}else 
					Write(connfd, buf, nread);
					
				if (--nready <= 0)
					break;
			}
		}
	}
	return 0;
}
