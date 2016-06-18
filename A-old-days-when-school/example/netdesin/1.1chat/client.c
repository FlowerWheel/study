#include "../apue.h" 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define SERV_PORT 9875

void RW(int fd_from, int fd_to)
{
	ssize_t		n;
	char		buf[MAXLINE];
again:
	while ((n = read(fd_from, buf, MAXLINE)) > 0)
		if(write(fd_to, buf, n) != n)
			err_sys("SendToServ : write error : %s\a\n", strerror(errno));
	if (n < 0 && n == EINTR)
		goto again;
	else if (n < 0)
		err_sys("SendToServ : read error : %s \a\n", strerror(errno));
}
void *ReadFromServ(void * arg)
{
	int sockfd = (int)arg;
//	printf("%d\n", sockfd);
	RW(sockfd, 1);
	pthread_exit(NULL);
}

void SendToServ(int fd)
{
	RW(0, fd);
}

int main (int argc, char *argv[])
{	
	struct  sockaddr_in	serv_addr;
	struct  hostent		*host;
	int		sockfd;
	char	strhost[16];
	pthread_t tid;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("Socket error : %s\a\n", strerror(errno));

	strcpy(strhost, "127.0.0.1");
	if ((host = gethostbyname(strhost)) == NULL)
		err_sys("Gethostbyname error\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port	 = htons(SERV_PORT);
//	serv_addr.sin_addr   = *((struct in_addr*)(host->h_addr_list[0]));
	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
		err_sys("inet_pton error for %s\a\n", argv[1]);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		err_sys("Connect error : %s\a\n", strerror(errno));

	if (pthread_create(&tid, NULL, ReadFromServ, (void*)sockfd) < 0)	
		err_sys("Pthread_create error : %s\a\n", strerror(errno));

	SendToServ(sockfd);
	return 0;
}
