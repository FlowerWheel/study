#include "myunp.h"
#include "header.h"

#define BRDPORT 9438

int main (int argc, char **argv)
{
	int		i, sockfd;
	const int on = 1;
	struct sockaddr_in brdaddr;
	char buf[MAXLINE];

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&brdaddr, sizeof(brdaddr));
	brdaddr.sin_family = AF_INET;
	brdaddr.sin_port = htons(BRDPORT);
	if(inet_pton(AF_INET, "192.168.1.255", &brdaddr.sin_addr) < 0)
		err_sys("inet_pton error");

	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	strcpy(buf, "hello");
	for (i = 0; i < 1000000; i++)
	{
		printf("send msg to 192.168.255. num = %d\n", i);
		sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&brdaddr, sizeof(brdaddr));
		sleep(1);
	}
	
	return 0;
}
