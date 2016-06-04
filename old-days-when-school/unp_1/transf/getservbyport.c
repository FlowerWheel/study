#include "myunp.h"

int main (int argc, char **argv)
{
	struct servent *sp;
	char **pptr;

	if (argc == 2){
		if((sp = getservbyport(htons(atoi(argv[1])), NULL)) == NULL)
			err_quit("getservbyname error for %s", argv[1]);
	}
	else if (argc == 3){
		if ((sp = getservbyport(htons(atoi(argv[1])), argv[2])) == NULL)
			err_quit("getservbyname error for %s : %s", argv[1], argv[2]);
	}
	else 
		err_quit("usage : %s <[port] [portname]>", argv[0]);

	printf("s_name : %s\n", sp->s_name);
	printf("s_port : %d\n", ntohs(sp->s_port));
	printf("s_proto : %s \n", sp->s_proto);
	printf("s_aliases : ");
	for (pptr = sp->s_aliases; *pptr != NULL; pptr++)
		printf("%s ", *sp->s_aliases);
	printf("\n");

	return 0;
}
