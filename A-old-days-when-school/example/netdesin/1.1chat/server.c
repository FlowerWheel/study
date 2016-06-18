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

int					Cli_Count = 0;
int					Cli_Fd_List[MAXFD];
struct	sockaddr_in Cli_Addr_List[MAXFD];
	

void DelCli (const int index)
{
	int			i;	
	time_t		ticks;
	char		buff[256], buf[16];
	struct sockaddr_in Offline_addr;

	Offline_addr = Cli_Addr_List[index];
	for (i = index; i <= Cli_Count; i++)
	{
		Cli_Fd_List[i] = Cli_Fd_List[i+1];
		Cli_Addr_List[i] = Cli_Addr_List[i+1];
	}
	Cli_Count--;
	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "Client Offline ：(%s:%d)%.24s\r\n",
			inet_ntop(AF_INET,&Offline_addr.sin_addr,buf,sizeof(buf)),
			ntohs(Offline_addr.sin_port),
			ctime(&ticks));
	for (i = 0; i <= Cli_Count; i++)
		if (write(Cli_Fd_List[i], buff, strlen(buff)) < 0)
			err_sys("RecvAndSend : write error : %s\n", strerror(errno));

}
void RW(int index)
{
	ssize_t		n;
	int			i;
	char		buf[MAXLINE];	

again:
	while ((n = read(Cli_Fd_List[index], buf, MAXLINE)) > 0)
	{
		for (i = 1; i <= Cli_Count; i++)
		{
			if (i == index)
				;
			else 
			   if (write(Cli_Fd_List[i], buf, n) != n)
				err_sys("RecvAndSend : write error : %s\n", strerror(errno));
		}
	}
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("RecvAndSend : read error : %s\n", strerror(errno));
}
void *RecvAndSend (void *index)
{
	RW((int)index);
	DelCli((int)index);
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
	int		i, index;
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

	Cli_Fd_List[0] = 0;
	Cli_Addr_List[0] = servaddr;

	if (pthread_create(&tid, NULL, SendToCli, NULL) != 0)
			err_sys("pthread_create error\n");

	while (1)
	{
		socklen_t addrlen = sizeof( clientaddr );
		if((connfd = accept(sockfd,(struct sockaddr *)&clientaddr, &addrlen)) <= 0)
			err_sys("accept error :%s \a\n", strerror(errno));

		index = Cli_Count;
		Cli_Fd_List[++Cli_Count] = connfd;
		Cli_Addr_List[Cli_Count]= clientaddr;

		fprintf(stdout, "CliCount = %d\tFdLst: ", Cli_Count);
		for (i = 1; i <= Cli_Count; i++)
			printf ("%d  ", Cli_Fd_List[i]);
		printf("\n");

		ticks = time(NULL);
		printf ("Connect from %s:%d %s\n",
			   	inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)),
			   	ntohs(clientaddr.sin_port),
			   	ctime(&ticks));
		snprintf(ansBuf, sizeof(ansBuf), "Connect to Server(%s:%d) success：%.24s\r\n",
				inet_ntop(AF_INET, &servaddr.sin_addr, buff, sizeof(buff)),
			   	ntohs(clientaddr.sin_port),
			   	ctime(&ticks));
		if (write(connfd, ansBuf, strlen(ansBuf)) < 0)
			err_sys("Write error : %s\n", strerror(errno));

		if (pthread_create(&tid, NULL, RecvAndSend, (void *)index) != 0)
			err_sys("pthread_create error\n");
	}
	
	exit(EXIT_SUCCESS);
}
