#include "myunp.h"

#define PORT 6789

int main (int argc, char **argv)
{
	int		sockfd;
	socklen_t	len;
	struct sockaddr_in	cliaddr, servaddr;
	char	str[INET_ADDRSTRLEN];

	if (argc != 2)
		err_quit("usage : %s <IPaddress>", argv[0]);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family =	AF_INET;
	servaddr.sin_port	=	htons (PORT);
	if (inet_pton (AF_INET, argv[1], &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");
/*
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");
*/
	bzero(&cliaddr, sizeof(cliaddr));
	len = sizeof (cliaddr);

	if (getsockname (sockfd, (struct sockaddr*)&cliaddr, &len) < 0)
		err_sys("getsockname error");
	printf("local address %s : %d\n", inet_ntop(AF_INET, (struct sockaddr *)&cliaddr, str, len), ntohs(cliaddr.sin_port));

	dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return 0;
}
