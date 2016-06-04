#include "../apue.h" 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>

#define LISTENQ  100 
#define MAXFD	 1000
#define PORTNUM  9875

int	 CliCount = 0;
int	 Cli_Fd_List[MAXFD];
struct	sockaddr_in Cli_Addr_List[MAXFD];

void DelCli (const int fd)
{
	int			i;	
	time_t		ticks;
	char		buff[256], buf[16];
	struct sockaddr_in Offline_addr;
	for (i = 0; i < CliCount; i++)
		if (Cli_Fd_List[i] == fd)
		{
			Offline_addr = Cli_Addr_List[i];
			for (; i < CliCount; i++)
			{
				Cli_Fd_List[i] = Cli_Fd_List[i+1];
				Cli_Addr_List[i] = Cli_Addr_List[i+1];
			}
			CliCount--;
		}
	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "Offline ：(%s:%d)%.24s\r\n",
			inet_ntop(AF_INET, &Offline_addr.sin_addr, buf, sizeof(buf)),
			ntohs(Offline_addr.sin_port),
			ctime(&ticks));
//	printf("%s\n", buff);
	for (i = 0; i < CliCount; i++)
		if ( write(Cli_Fd_List[i], buff, strlen(buff)) < 0)
			err_sys("RecvAndSend : write error : %s\n", strerror(errno));
	if ( write(1, buff, strlen(buff)) < 0)
			err_sys("RecvAndSend : write error : %s\n", strerror(errno));

}
void RW(int fd_from)
{
	ssize_t		n;
	int			i;
	char		buf[MAXLINE];
	
again:
	while ((n = read(fd_from, buf, MAXLINE)) > 0)
	{
		for (i = 0; i < CliCount; i++)
		{
			if (fd_from != Cli_Fd_List[i])
			if ( write(Cli_Fd_List[i], buf, n) != n)
				err_sys("RecvAndSend : write error : %s\n", strerror(errno));
		}
	}
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("RecvAndSend : read error : %s\n", strerror(errno));
	DelCli(fd_from);
	pthread_exit(NULL);

}
void *RecvAndSend (void *arg)
{
	RW((int)arg);
	DelCli((int)arg);
	pthread_exit(NULL);
}
void *SendToCli(void *arg)
{
	RW(0);
	pthread_exit(NULL);
}

int main (void)
{
	int		sockfd, connfd;
	int		i;
	struct	sockaddr_in	servaddr, clientaddr;
	time_t  ticks;
	char	ansBuf[256], buff[16];
	pthread_t	tid;	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)	
		err_sys("Socket error : %s\a\n", strerror(errno));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORTNUM);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)	
		err_sys("Bind error : %s\a\n", strerror(errno));

	if (listen(sockfd, LISTENQ) < 0)
		err_sys("Listen error : %s\a\n", strerror(errno));

	printf("服务器已启动，等待客户链接\n\n");

//	signal(SIGTERM, servclose);

	if (pthread_create(&tid, NULL, SendToCli, NULL) != 0)
			err_sys("pthread_create error\n");

	while (1)
	{
		socklen_t addrlen = sizeof( clientaddr );
		if((connfd = accept(sockfd,(struct sockaddr *)&clientaddr, &addrlen)) <= 0)
			err_sys("accept error :%s \a\n", strerror(errno));

		Cli_Fd_List[CliCount] = connfd;
		Cli_Addr_List[CliCount++]= clientaddr;

		fprintf(stdout, "%d\t", CliCount);
		for (i = 0; i < CliCount; i++)
			printf ("%d  ", Cli_Fd_List[i]);
		printf("\n");

		ticks = time(NULL);
		printf ("Connect from %s:%d %s\n",
			   	inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)),
			   	ntohs(clientaddr.sin_port),
			   	ctime(&ticks));
		snprintf(ansBuf, sizeof(ansBuf), "你已经成功连接服务器(%s:%d)：%.24s\r\n",
				inet_ntop(AF_INET, &servaddr.sin_addr, buff, sizeof(buff)),
			   	ntohs(clientaddr.sin_port),
			   	ctime(&ticks));

		write(connfd, ansBuf, strlen(ansBuf));

		if (pthread_create(&tid, NULL, RecvAndSend, (void *)connfd) != 0)
			err_sys("pthread_create error\n");
	}
	
	exit(EXIT_SUCCESS);
}
