#include "myunp.h"

#define		SERVPORT 6788	

int main(int argc, char **argv)
{
	struct sockaddr_in	servaddr;
	int		connfd;

	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero (&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVPORT);

	if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) < 0)
		err_sys("inet_pton error");

	if (connect(connfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");
	
	str_cli(stdin, connfd);

	return 0;
}
