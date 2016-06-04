#include "myunp.h"

int main(int argc, char **argv)
{
	int		sockfd;
	
	if (argc != 3)
		err_quit("usage: tcpsendoo01 <host> <port#>");

	sockfd = tcp_connect(argv[1], argv[2]);

	Write(sockfd, "123", 3);
	printf("wrote 3 bytes normal data\n");
	sleep(1);

	Send(sockfd, "4", 1, MSG_OOB);
	printf("send 1 byte OOB data\n");
	sleep(1);

	Write(sockfd, "567", 3);
	printf("wrote 3 bytes normal data\n");
	sleep(1);

	Send(sockfd, "8", 1, MSG_OOB);
	printf("send 1 byte OOB data\n");
	sleep(1);

	Write(sockfd, "9", 3);
	printf("wrote 1 bytes normal data\n");
	sleep(1);

	exit(0);
}
