#include "myunp.h"

#define PORT 6789

int main (int argc, char **argv)
{
	int		sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage : %s <IPaddress>", argv[0]);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)//the argment 3 need carefull
		err_sys("inet_pton error");

	dg_cliaddr(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	return 0;
}
