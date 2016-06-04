#include "../apue.h" 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define LISTENQ 20
#define PORTNUM 8886
#define MAXFD	20

int  sockfd, i;
static int maxi = 0;
static int client[MAXFD];

void *recvandsend(void *arg)
{
	int index = 0;
	int nbytes = 0;
	int outindex = 0;
	char buffer[1024];
	printf("*************接收转发线程启动**************");
	while (1)
	{
		if (maxi > 0)
		{
			for (index = 0; index < maxi; index++){
				memset(buffer, 0, sizeof(buffer));
				nbytes = 0;
				nbytes = read(client[index++], buffer, sizeof(buffer));
				printf("%d, %d\n", index, client[index]);
				if (nbytes > 0){
					buffer[nbytes] = '\0';
					for (outindex = 0; (outindex != index) && (outindex < maxi); outindex++)
						if (write(client[outindex++], buffer, sizeof(buffer)) == -1)
							err_sys("Write error:%s\a\n", strerror(errno));
				}
			}
		}
	}
	pthread_exit(NULL);
	
}

int main (int argc, char **argv)
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	pthread_t		p_thread;
	socklen_t		sin_size;
	int		thr_id,new_fd = 0;
	if (argc != 1)
		err_quit("Usage : %s \a \n", argv[0]);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		err_sys("Socket error:%s\a\n", strerror(errno));

	memset(client, 0, sizeof(client));

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORTNUM);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1 )
		err_sys("Bind error: %s\a\n",strerror(errno));
	printf("服务器监听端口:%d ...", PORTNUM);
	
	if (listen(sockfd, LISTENQ) == -1)
		err_sys("Listen error%s\a\n", strerror(errno));

	thr_id = pthread_create(&p_thread, NULL, recvandsend, NULL);

	printf("欢迎来到本聊天室\n");

	while (1)
	{
		if (maxi >= 20)	
		{
			printf("已达人数上限\n");
			continue;
		}
		sin_size =(socklen_t)(sizeof (struct sockaddr_in));
		if ((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size)) == -1)
			err_sys("Accept error: %s\a\n", strerror(errno));
		client[maxi++] = new_fd;
		printf("\n新用户进入聊天室,聊天室当前在线人数位%d\n", maxi);
	}
	close(sockfd);
	return 0;
}
