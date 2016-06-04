#include <string.h>
#include <errno.h>  /* for strerror */
#include <stdio.h>

int main(int argc,  char ** argv)
{ 
	int		i;

	for(i = 0; i < 133; i++)
		printf("errno.%03d is: %s\n",  i,  strerror(i));
	return 0;
}
