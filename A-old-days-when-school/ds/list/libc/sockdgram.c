#include "lueap.h"

void dg_echo(int sockfd, struct sockaddr* PtrCliAddr, socklen_t clilen)
{
	int		n;
	char	mesg[MAXLINE];
	socklen_t	len;
	for(;;)
	{
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, PtrCliAddr, &len);
		Sendto(sockfd, mesg, n, 0, PtrCliAddr, len);
		bzero(mesg, MAXLINE);
	}
}

void dg_echoaddr(int sockfd, struct sockaddr* PtrCliAddr, socklen_t clilen)
{
	char	mesg[MAXLINE];
	char	str[INET_ADDRSTRLEN];
	socklen_t	len;

	bzero(mesg, MAXLINE);

	while (1)
	{
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, PtrCliAddr, &len);
		Sendto(sockfd, mesg, strlen(mesg), 0, PtrCliAddr, len);
		bzero(mesg, MAXLINE);
		printf("client address  %s : %d\n", 
				inet_ntop(AF_INET, (struct sockaddr_in *)PtrCliAddr, str, len), 
				ntohs(((struct sockaddr_in *)PtrCliAddr)->sin_port));
		printf("***********************************************\n");
	}
}

static void recvfrom_int(int signo);
static void recvfrom_alarm(int signo);
static int	count = 0;

void dg_echoloop1(int sockfd, struct sockaddr* PtrCliAddr, socklen_t clilen)
{
	char	mesg[MAXLINE];
	socklen_t	len;

	if (signal(SIGINT, recvfrom_int) == SIG_ERR)
		err_sys("signal error");

	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("signal error");
	alarm(1);

	for(;;)
	{
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, PtrCliAddr, &len);
		count ++;
//		Sendto(sockfd, mesg, n, 0, PtrCliAddr, len);
//		fputs(mesg, stdout);
//		bzero (mesg, MAXLINE);
	}
}

void dg_echoloop2(int sockfd, struct sockaddr* PtrCliAddr, socklen_t clilen)
{
	int		n = 220 * 1024;
	char	mesg[MAXLINE];
	socklen_t	len;

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)) < 0)
		err_sys("setsockopt error");

	if (signal(SIGINT, recvfrom_int) == SIG_ERR)
		err_sys("signal error");

	if (signal(SIGALRM, recvfrom_alarm) == SIG_ERR)
		err_sys("signal error");
	alarm(1);


	for(;;)
	{
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, PtrCliAddr, &len);
		count ++;
//		Sendto(sockfd, mesg, n, 0, PtrCliAddr, len);
//		fputs(mesg, stdout);
//		bzero (mesg, MAXLINE);
	}
}

static void recvfrom_int(int signo)
{
	printf ("\nreceived %d datagrams\n", count);
	exit (0);
}

static void recvfrom_alarm(int signo)
{
	printf ("\nreceived %d datagrams\n", count);
	alarm(1);
}

void dg_cli(FILE *fp, int sockfd, struct sockaddr *PtrServAddr, socklen_t addrlen)
{
	int		n;
//	struct	sockaddr_in		servaddr;
	char	sendline[MAXLINE], recvline[MAXLINE];
//	socklen_t		servaddrlen;

	while (fgets(sendline, MAXLINE, fp) != NULL)
	{
		Sendto(sockfd, sendline, strlen(sendline), 0, PtrServAddr, addrlen);
//		servaddrlen = sizeof(servaddr);
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;
		fputs(recvline, stdout);
		bzero(sendline, sizeof(sendline));
		bzero(recvline, sizeof(sendline));
	}
}

void dg_cliaddr(FILE *fp, int sockfd, struct sockaddr *PtrServAddr, socklen_t addrlen)
{
	int		n;
	struct	sockaddr_in		servaddr, *pservaddr = (struct sockaddr_in *)PtrServAddr;
	char	sendline[MAXLINE], recvline[MAXLINE];
	char	addrbuf[INET_ADDRSTRLEN];
	socklen_t		servaddrlen;

	while (fgets(sendline, MAXLINE, fp) != NULL)
	{
		Sendto(sockfd, sendline, strlen(sendline), 0, PtrServAddr, addrlen);
		servaddrlen = sizeof(servaddr);
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *)&servaddr, &servaddrlen);
		
		if ( addrlen != servaddrlen /* || memcmp(&servaddr.sin_addr, &(pservaddr->sin_addr), INET_ADDRSTRLEN) != 0*/){
			printf("reply from %s (ignored)", inet_ntop(AF_INET, &servaddr.sin_addr, addrbuf, sizeof(addrbuf)));
			printf("%s\n", inet_ntop(AF_INET, &(pservaddr->sin_addr), addrbuf, sizeof(addrbuf)));
			printf("%d %d\n", addrlen, servaddrlen);
			printf("%d\n", memcmp(&servaddr, PtrServAddr, addrlen));

		}

		recvline[n] = 0;
		fputs(recvline, stdout);
		bzero(&servaddr, sizeof(servaddr));
		bzero(recvline, sizeof(recvline));
	}
}


