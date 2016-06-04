#include "myunp.h"
#include <sys/ioctl.h>

int Socket(int family, int type, int protocol)
{
	int sockfd;
	if ((sockfd = socket(family, type, protocol)) == -1)
		err_sys("socket error");
	return sockfd;
}

void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	if (connect(sockfd, servaddr, addrlen) == -1)
		err_sys("connect error");
}

void Bind(int sockfd, const struct sockaddr *localaddr, socklen_t addrlen)
{
	if (bind(sockfd, localaddr, addrlen) == -1)	
		err_sys("bind error");
	return ;
}

void Listen(int fd, int backlog)
{
	char	*ptr;
	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

int Accept(int listenfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int	connfd;
	if ((connfd = accept(listenfd, cliaddr, addrlen)) == -1)
	{
		/**
		// if want to judge interupt by signal
		// use this
		if (errno == EINTR)
			continue;
		else
		**/
			err_sys("accept error");
	}
	return connfd;
}

ssize_t Recv(int sockfd, void *buff, size_t len, int flags)
{
	ssize_t		n;
	if ((n = recv(sockfd, buff, len, flags)) == -1)
		err_sys("recv error");
	return n;
}

ssize_t Send(int sockfd, void *buff, size_t len, int flags)
{
	ssize_t		n;
	if ((n = send(sockfd, buff, len, flags)) == -1)
		err_sys("send error");
	return n;
}

ssize_t Recvfrom(int sockfd, void *buff, ssize_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen)
{
	ssize_t		n;
	if ((n = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
		err_sys("recvfrom error");
	return n;
}

ssize_t Sendto(int sockfd, const void *buff, ssize_t nbytes, int flags, struct sockaddr *from, socklen_t addrlen)
{
	ssize_t n;
	if (( n = sendto(sockfd, buff, nbytes, flags, from, addrlen)) != nbytes)
		err_sys("recvfrom error");
	return n;
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	if (setsockopt(sockfd, level, optname, optval, optlen) == -1)
		err_sys("setsockopt error");
}

void Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
	if (getsockopt(sockfd, level, optname, optval, optlen) == -1)
		err_sys("setsockopt error");
}

void Socketpair(int domain, int type, int protocol, int sv[2])
{
	if (socketpair(domain, type, protocol, sv) == -1)
		err_sys("socketpair error");
}

/*
int Select(int nfds,  fd_set *readfds,  fd_set *writefds, fd_set *exceptfds,  struct timeval *timeout)
{
	int		n;

	if ((n = select(nfds, *readfds, *writefds, *exceptfds, *timeout)) == -1)
		err_sys("select error");
	return n;

}
*/

int Sockatmask(int fd)
{
	int		flag;

	if (ioctl(fd, SIOCATMARK, &flag) < 0)
		return -1;
	return (flag != 0);
}


int readable_timeo(int fd, int sec)
{
	fd_set	rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	return (select(fd+1, &rset, NULL, NULL, &tv));
}

/*
static void connect_alarm(int signo)
{
	return ;
}

int connect_timeo(int sockfd, struct sockaddr* saptr, socklen_t salen, int nsec)
{
	sighandler_t	*sigfunc;
	int				n;

	sigfunc = Signal(SIGALRM, connect_alarm);

	if (alarm(nsec) != 0)
		err_msg("connect_timeo: alarm already set");

	if ((n = connect(sockfd, saptr, salen)) < 0)
	{
		close(sockfd);
		if (errno = EINTR)
			errno = ETIMEOUT;
	}

	alarm(0);
	Signal(SIGALRM, sigfunc);
}
*/


