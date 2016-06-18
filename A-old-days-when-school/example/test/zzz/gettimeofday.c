#include <stdio.h>
#include <sys/time.h>

int main (void)
{
	struct timeval time[10000];
	int timesub[100];
	int i;

	for(i = 0; i < 10000; i++)
	{
		gettimeofday(&time[i], NULL);
	}
	
	for(i = 0; i < 10000 - 1; i++)
	{
		timesub[time[i+1].tv_usec - time[i].tv_usec] ++;
	}
	printf("%d\n", time[9999].tv_usec - time[0].tv_usec);
	for(i = 0; i < 100; i++)
		if (timesub[i] != 0)
			printf("%d  %d time\n", i, timesub[i]);
	return 0;
}
