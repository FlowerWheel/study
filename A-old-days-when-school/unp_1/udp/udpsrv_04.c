#include "myunp.h"

#define PORT 6789

int main (int argc, char **argv)
{
	int		sockfd;
	struct sockaddr_in	servaddr, cliaddr;
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		err_sys("socket error : %s", strerror(errno));

	servaddr.sin_family	= AF_INET;
	servaddr.sin_port	= htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error : %s", strerror(errno));

	dg_echoloop1(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	return 0;
}
