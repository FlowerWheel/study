#include "myunp.h"

int main (int argc, char **argv)
{
	struct addrinfo *ptr, *result, hints;
	struct sockaddr_in *addrbuf;

	bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0)
		err_sys("getaddrinfo error %s", gai_strerror(errno));

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)	
	{
		addrbuf = (struct sockaddr_in *)ptr->ai_addr;
		printf("ai_flags : %d\n", ptr->ai_flags);
		printf("ai_family : %d\n", ptr->ai_family);
		printf("ai_socktype : %d\n", ptr->ai_socktype);
		printf("ai_protocol : %d\n", ptr->ai_protocol);
		printf("ai_addrlen : %d\n", (int)ptr->ai_addrlen);
		printf("AI_CANONNAME : %s\n", ptr->ai_canonname);
		printf("sin_port : %d\n", ntohs(addrbuf->sin_port));
		printf("sin_addr : %s\n\n", inet_ntoa(addrbuf->sin_addr));

	}

	freeaddrinfo(result);
	return 0;
}
