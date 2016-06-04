#include "myunp.h"
#include <limits.h>
#include <poll.h>

#define SERVPORT 6688 
#define OPEN_MAX 1024

int main (int argc, char **argv)
{
	struct sockaddr_in	servaddr, cliaddr;
	struct pollfd	client[OPEN_MAX];
	socklen_t	calen;
	ssize_t	nread;
	int		i, maxi, nready;
	int		sockfd, connfd;
	char	buf[MAXLINE];

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	Listen(sockfd, LISTENQ);

	client[0].fd = sockfd;
	client[0].events = POLLRDNORM;

	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;
	maxi = 0;
	while(1)
	{
		if ((nready = poll(client, maxi + 1, 100)) == -1)
			err_sys("poll error");
		
		if (client[0].revents & POLLRDNORM)
		{
			calen = sizeof(cliaddr);
			connfd = Accept(sockfd, (struct sockaddr *)&cliaddr, &calen);
			for (i = 1; i < OPEN_MAX; i++)
				if(client[i].fd == -1)
				{
					client[i].fd = connfd;
					client[i].events = POLLRDNORM;
					break;
				}
			if (i == OPEN_MAX)
				err_quit("too many clients");
			if (i > maxi)
				maxi = i;
			if (--nready <= 0)
				continue;
		}

		for (i = 1; i <= maxi; i++)
		{
			if (((connfd = client[i].fd) != -1) && (client[i].revents &(POLLRDNORM | POLLERR)))
			{
				if ((nread = read(connfd, buf, MAXLINE)) < 0)
				{
					if (errno == ECONNRESET)
					{
						Close(connfd);
						client[i].fd = -1;
					}else 
						err_sys("read error");
				}else if (nread == 0){
					Close(connfd);
					client[i].fd = -1;
				}else
					Write(connfd, buf, nread);

				if (--nready <= 0)
					break;
			}
		}
	}
	return 0;
}
