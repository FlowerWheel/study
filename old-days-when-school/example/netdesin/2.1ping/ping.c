#include "../apue.h"
#include "ping.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#define BUFSIZE		1024

int			datalen = 56;
char		*host; 
int			nsent;
pid_t		pid;
int			sockfd;
int			verbose;

void readloop(void);
void sig_alm(int);
void tv_sub(struct timeval *, struct timeval *);

int main (int argc, char **argv)
{
	int			c;
	struct addrinfo *ai;
	char		*h;

	opterr = 0;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		err_sys("Socket error : %s \a\n", strerror(errno));
	exit(EXIT_FAILURE);
}
