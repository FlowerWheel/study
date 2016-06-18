#include "myunp.h"

int main (int argc, char **argv)
{
	char *ptr, **pptr;
	char str_addr[INET_ADDRSTRLEN];
	struct in_addr	inaddr;
	struct hostent	*hptr;

	while (--argc > 0){
		ptr = *++argv;
		bzero(&inaddr, sizeof(inaddr));
		if (inet_pton(AF_INET, ptr, &inaddr) < 0)
			err_sys("inet_pton error");

		if ((hptr = gethostbyaddr(&inaddr, sizeof(inaddr), AF_INET)) == NULL){
			printf("gethostbyaddr error for host:%s :%s\n", ptr, hstrerror(h_errno));
			continue;
		} 

		printf("h_name : %s\n", hptr->h_name);
		printf("h_aliases:");
		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("%s	", *pptr);
		printf("\n");

		switch (hptr->h_addrtype){
			case AF_INET:

				pptr = hptr->h_addr_list;
				printf("h_addr_list:");
				for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
					printf("%s", inet_ntop(hptr->h_addrtype, *pptr, str_addr, sizeof(str_addr)));
				printf("\n");
				break;
			default:
				err_msg("unknow address type");
				break;
		}
	}
	return 0;
}
