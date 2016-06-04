#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (void)
{
	time_t	ttime = time(NULL);
	printf("asctime localtime : %s", asctime(localtime(&ttime)));
	printf("asctime gmtime    : %s", asctime(gmtime(&ttime)));
	printf("ctime             : %s", ctime(&ttime));
	return 0;
}
