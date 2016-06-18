#include "myunp.h"
#include "header.h"

#define BRDPORT 9438

int main (int argc, char **argv)
{
	int		n, 	sockfd;
	char	recvline[MAXLINE];
	struct sockaddr_in preply_addr;
	struct sockaddr_in brdaddr;
	socklen_t len;
	const int on = 1;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&brdaddr, sizeof(brdaddr));
	brdaddr.sin_family = AF_INET;
	brdaddr.sin_port = htons(BRDPORT);
	brdaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	if(inet_pton(AF_INET, "192.168.1.255", &brdaddr.sin_addr) < 0)
//		err_sys("inet_pton error");

	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	Bind(sockfd, (struct sockaddr *)&brdaddr, sizeof(brdaddr));

	while(1)
	{
		printf("****************************************\n");
		len = sizeof(preply_addr);
		n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) &preply_addr, &len);
		printf("****************************************\n");
		len = sizeof(preply_addr);
		if (n < 0)
		{
			if (errno == EINTR)
				break;
			else
				err_sys("recvfrom error");
		} else {
			recvline[n] = 0;
			printf("from %s: %s", sock_ntop((struct sockaddr *)&preply_addr, len), recvline);
		}
		printf("recv msg from 192.168.255\n");
	}
	return 0;
}
