#include "lueap.h"

void str_echo(int fd)
{
	char	buf[MAXLINE];
	ssize_t	n = 1;

	while(1){
		while((n = read(fd, buf, MAXLINE)) > 0)
			if (write(fd, buf, n) != n)
				err_sys("write error");
		printf("%d\n", n);
		if (n < 0 && errno == EINTR)
			continue;
		else if(n <= 0)
			err_sys("str_echo : read error");

	}
/*
again:
	while ((n = read(fd, buf, MAXLINE)) > 0){
		if (write(fd, buf, n) != n)
			err_sys("write error");
	}
	printf("%d\n", n);
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n <= 0)
		err_sys("str_echo : read error");
*/

}

void str_cli(FILE *fp, int  sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	for(;;)
	{
		bzero(sendline, sizeof(sendline));
		bzero(recvline, sizeof(recvline));

		if (fgets(sendline, MAXLINE, fp) == NULL && ferror(fp))
			err_sys("fgets error");

		if (write(sockfd, sendline, strlen(sendline)) != strlen(sendline))
			err_sys("write error");
		
		if (readline1(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli : server terminated prematurely");
		fputs(recvline, stdout);
	}
}

/*
void str_cliselect(FILE *fp, int  sockfd)
{
	int		maxfdp1;
	char	sendline[MAXLINE], recvline[MAXLINE];
	fd_set	rset;

	FD_ZERO(&rset);

	while(1){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);

		maxfdp1 = fileno(fp) > sockfd ? fileno(fp) + 1 : sockfd + 1;

		if (select(maxfdp1, &rset, NULL, NULL, NULL) < 0)	
			err_sys("select error");

		if (FD_ISSET(sockfd, &rset))
		{
			if (readline1(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli : server terminated prematurely");
			fputs(recvline, stdout);

		}
		if (FD_ISSET(fileno(fp), &rset))
		{
			if (fgets(sendline, MAXLINE, fp) == NULL && ferror(fp))
				err_sys("fgets error");
		}
	}
}
*/
