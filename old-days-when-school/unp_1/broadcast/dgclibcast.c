#include "myunp.h"

static void recvfrom_alarm(int signo)
{
	return ;
}

void dg_cli_bcast1(int sockfd, struct sockaddr * pservaddr, socklen_t servlen)
{
	int n;
	char recvline[MAXLINE];
	socklen_t len;
	struct sockaddr *preply_addr;

	preply_addr = Malloc(servlen);

	Signal(SIGALRM, recvfrom_alarm);

//	alarm(5);
	while(1)
	{
		len = servlen;
		n = recvfrom(sockfd, recvline, MAXLINE, 0, pservaddr, &len);
		if (n < 0)
		{
			if (errno == EINTR)
				break;
			else
				err_sys("recvfrom error");
		} else {
			recvline[n] = 0;
			printf("from %s: %s", sock_ntop(preply_addr, len), recvline);
		}
		printf("recv msg from 192.168.255\n");
	}
	free(preply_addr);
}
