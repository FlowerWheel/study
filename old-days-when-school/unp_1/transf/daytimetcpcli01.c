#include "myunp.h"

int main (int argc, char **argv)
{
	int	sockfd, n;
	struct sockaddr_in servaddr;
	char	recvline[MAXLINE+1];
//	char	str[INET_ADDRSTRLEN];
	
	struct addrinfo *ptr, *result, hints;
	struct sockaddr_in *addrbuf;

	bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;

	if (argc != 3)
		err_quit("usage:%s <host> <service>", argv[0]);

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0)
		err_sys("getaddrinfo error %s", gai_strerror(errno));

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		addrbuf = (struct sockaddr_in *)ptr->ai_addr;
		printf("sin_port : %d\n", (addrbuf->sin_port));
//		printf("sin_port : %d\n", htons(13));
		printf("sin_addr : %s\n", inet_ntoa(addrbuf->sin_addr));

		sockfd = Socket(addrbuf->sin_family, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		bcopy(addrbuf, &servaddr, sizeof(struct sockaddr_in)); //将getaddrinfo返回的struct sockaddr结构直接
		//复制给一个地址结构是可以的，该结构里面的内容可以直接使用。而不需要host->net字节序的转换。
//		servaddr.sin_family = addrbuf->sin_family;
//		servaddr.sin_family = AF_INET;
//		servaddr.sin_port = addrbuf->sin_port; 
//		servaddr.sin_port = htons(13);
//		memcpy(&servaddr.sin_addr, &addrbuf->sin_addr, sizeof(struct in_addr));
//		bcopy(&addrbuf->sin_addr, &servaddr.sin_addr, sizeof(struct in_addr));
		if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == 0)
		{
			printf("connected\n");
			break;
		}
		err_ret("connect error");
		close(sockfd);
	}

	freeaddrinfo(result);

	if (ptr == NULL)
		err_quit("unable to connect");

	while ((n = read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
	return 0;
}
