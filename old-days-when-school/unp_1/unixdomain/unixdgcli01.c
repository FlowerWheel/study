#include "myunp.h"


int main (int argc, char **argv)
{
	int		sockfd;
	struct sockaddr_un servaddr, cliaddr;

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sun_family = AF_LOCAL;
	strncpy(cliaddr.sun_path, tmpnam(NULL), strlen(cliaddr.sun_path) - 1);

	Bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strncpy(servaddr.sun_path, "UNIXSTR_PATH", strlen(servaddr.sun_path) - 1);
	
	dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return 0;
}
