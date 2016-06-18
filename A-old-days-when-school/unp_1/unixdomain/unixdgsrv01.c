#include "myunp.h"


int main (int argc, char **argv)
{
	int		sockfd;
	struct sockaddr_un servaddr, cliaddr;

	sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

	unlink("UNIXSTR_PATH");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strncpy(servaddr.sun_path, "UNIXSTR_PATH", strlen(servaddr.sun_path) - 1);
	
	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

	return 0;
}
