#include <string.h>
#include <errno.h>  /* for strerror */
#include <stdio.h>
#include <signal.h>

int main(int argc,  char ** argv)
{ 
	int		i;

	for(i = 0; i < 32; i++)
		printf("errno.%03d is: %s\n",  i,  sys_siglist[i]);
	return 0;
}
