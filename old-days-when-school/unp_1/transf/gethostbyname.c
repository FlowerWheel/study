#include "myunp.h"

int main (int argc, char **argv)
{
	char *ptr, **pptr;
	char str_addr[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while (--argc > 0){
		ptr = *++argv;
		if ((hptr = gethostbyname(ptr)) == NULL){
			err_msg("gethostbyname error for host:%s : %s", ptr, hstrerror(h_errno));
			continue;
		}
		printf("h_name : %s \n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("h_aliases : %s\n", *pptr);

		switch (hptr->h_addrtype){
			case AF_INET:
				
				printf("h_addr_list: ");
				for ( pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
					printf("%s	", inet_ntop(hptr->h_addrtype, *pptr, str_addr, sizeof(str_addr)));
				printf("\n");

				break;
			default:
				err_ret("unknow address type");
		}
	}
	return 0;
}
