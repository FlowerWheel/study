#include "../apue.h" 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define PORTNUM 8886

static int sockfd;

void* recvfromserver(void *arg)
{
	char message[1024];
	int	 nbytes = 0;
	while (1)
	{
		memset(message, 0, sizeof(message));
		nbytes = read(sockfd, message, sizeof(message));
		if (nbytes > 0)
		{
			message[nbytes] = '\0';
			printf("%s\n", message);
		}
	}
	pthread_exit(NULL);
}

int main (int argc, char **argv)
{
	struct sockaddr_in server_addr;
	struct hostent		*host;
	pthread_t p_thread;
	int		thr_id;
	char	buffer[1024];
	char	strhost[16];
	char	clientname[20];
	char	message[1024];

	if (argc != 1)
		err_quit("Usage : %s\a\n", argv[0]);
	
	//printf("请输入服务器IP地址:");
	//scanf("%s", strhost);
	strcpy(strhost, "127.0.0.1");
	if ((host = gethostbyname(strhost)) == NULL)
		err_sys("Gethostbyname error\n");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		err_sys("Socket error:%s\a\n", strerror(errno));

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORTNUM);
	server_addr.sin_addr = *((struct in_addr*)(host->h_addr_list[0]));

	printf("套接口创建成功,正在链接到服务器...\n");
	
	if (connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1)
		err_sys("connect error %s\a\n", strerror(errno));
	
	printf("服务器链接成功!欢迎来到聊天室\n");
	printf("请输入您的用户昵称\n");
	scanf("%s", clientname);
	printf("****************************\n");	
	thr_id = pthread_create(&p_thread, NULL, recvfromserver, NULL);
	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		memset(message, 0, sizeof(message));
		scanf("%s", buffer);
		printf("****************************\n");	
		strcat(message, clientname);
		strcat(message, ":  ");
		strcat(message, buffer);
		printf("****************************\n");	
		if (write(sockfd, message, sizeof(message)) == -1)
			err_sys("write error %s\a\n", strerror(errno));
		if (strcmp(buffer, "Quit") == 0)
			break;
	}
	close(sockfd);
	return 0;
}
