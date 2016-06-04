#include "myunp.h"

int main (int argc, char ** argv)
{
	int listenfd, connfd;
	struct sockaddr_in	cliaddr, servaddr;
	socklen_t calen;
	char buf[MAXLINE];
	time_t	ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for (;;){
		calen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, (socklen_t *)&calen);

		ticks = time(NULL);

		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));
		close(connfd);
	}
	return 0;
}
