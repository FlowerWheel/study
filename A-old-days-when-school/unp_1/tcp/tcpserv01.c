#include "myunp.h"

#define		SERVPORT  6788

int main(int argc, char **argv)
{
	int		listenfd, connfd;
	struct sockaddr_in	servaddr, cliaddr;
	socklen_t	calen;
	pid_t	childpid;
	
	void sig_chld(int);

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero (&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //listen all IP

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("bind error");

	Listen(listenfd, 5);
	
	if (signal(SIGCHLD, sig_chld) == SIG_ERR) // handle SIGCHLD
		err_sys("signal error");

	for(;;)
	{
		calen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &calen)) < 0)
		{//error handle
			if (errno == EINTR) //interupt by signal
				continue; //restart
			else
				err_sys("accept error");
		}

		if ((childpid = fork()) == 0)
		{
			close(listenfd);

			str_echo(connfd);

			exit(0);
		} else if (childpid == -1)
			exit(1);

		close(connfd);
	}
	return 0;
}
