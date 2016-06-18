#include "myunp.h"

/*
struct  addrinfo *GetHostInfo(const char *hostname, const char *service, int family, int socktype)
{
	struct addrinfo hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if (getaddrinfo(hostname, service, &hints, &res) != 0)
		return NULL;
	return res;
}

void FreeHostInfo(struct addrinfo *ai)
{
	freeaddrinfo(ai);
}
*/

int		sock_fd(const char *hostname, const char *service, int family, int socktype)
{
	int		sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
		err_quit("sock_fd getaddrinfo error for %s, %s : %s", hostname, service, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;
		else 
			break;
	} while((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("sock_fd create error for %s, %s", hostname, service);
	freeaddrinfo(ressave);

	return sockfd;
}

int		sock_connect(const char *hostname, const char *service, int family, int socktype)
{
	int		sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
		err_quit("sock_connect getaddrinfo error for %s, %s : %s", hostname, service, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;
		
		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		close(sockfd);
	} while((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("sock_connect error for %s, %s", hostname, service);
	freeaddrinfo(ressave);
	return sockfd;
}

int		sock_bind(const char *hostname, const char *service, int family, int socktype)
{
	int		sockfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
		err_quit("sock_bind error for %s, %s : %s", hostname, service, gai_strerror(n));

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
			if (sockfd < 0)
				continue;
		Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("udp_client error for %s, %s", hostname, service);

	freeaddrinfo(ressave);
	return sockfd;

}

int	sock_listen(const char *hostname, const char *service, int family, int socktype, socklen_t *addrlenp)
{
	int		listenfd, n;
	const int on = 1;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
		err_quit("sock_listen error for %s, %s : %s", hostname, service, gai_strerror(n));

	ressave = res;
	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (listenfd < 0)
			continue;
		
		Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		close(listenfd);
	} while((res = res->ai_next) != NULL);

	if (res == NULL)
		err_sys("tcp_connect error for %s, %s", hostname, service);
	
	Listen(listenfd, LISTENQ);

	if (addrlenp)
		*addrlenp = res->ai_addrlen;

	freeaddrinfo(ressave);
	return listenfd;
}
