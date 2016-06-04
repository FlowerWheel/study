#include "lueap.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	static char str[128];
	struct sockaddr_in	*sin;
	switch(sa->sa_family)
	{
		case AF_INET:
			{
				sin = (struct sockaddr_in *)sa;
				inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str));
				return str;
			}
		default:
			return NULL;
	}
	return NULL;
}
