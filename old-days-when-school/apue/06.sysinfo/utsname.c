#include "lueap.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main (void)
{
	struct utsname	utbuf;

	if (uname(&utbuf) == -1)
		err_sys("uname error");
	printf("%s", utbuf.sysname);
	printf(":%s", utbuf.nodename);
	printf(":%s", utbuf.release);
	printf(":%s", utbuf.version);
	printf(":%s", utbuf.machine);
	printf("\n");
	return 0;
}
