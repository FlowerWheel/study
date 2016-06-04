#include "myunp.h"

int main (int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE];
	socklen_t len;
	struct sockaddr_storage ss;

	if (argc != 3)
		err_quit("usage : %s <hostname/IPaddress> <service/port#>", argv[0]);

	sockfd = tcp_connect(argv[1], argv[2]);

	len = sizeof(ss);

//	getpeername(sockfd, (struct sockaddr *)&ss, &len);
//	printf("connected to %s\n", sock_ntop_host((struct sockaddr *)&ss, len));

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
	printf("*********************************\n");
	exit(EXIT_SUCCESS);
}
