#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAXNITEM		1000000
#define MAXNTHREADS		100

int		nitiems;
struct {
	pthread_mutex_t		mutex;
	int		buf[MAXNITEM];
	int		nput;
	int		nval;
} shared = {
	PTHREAD_MUTEX_INITIALIZER
};
void	*produce(void *), *consume(void *);

int main (int argc, char **argv)
{
	int			i, nthreads, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("usage : %s <#item> <#threads>", argv[0]);

	nitiems = min(atoi(argv[1]), MAXNITEM);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

//	Set_concurrency(nthreads);
	//pthread_setconcurrency(nthreads);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}

	for (i = 0; i < nthreads; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("cout[%d] = %d\n", i, count[i]);
	}

	Pthread_create(&tid_consume, NULL, consume, NULL);
	Pthread_join(tid_consume, NULL);
	return 0;
}

void *produce(void *arg)
{
	for ( ; ; )
	{
		Pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitiems)
		{
			Pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}	
		shared.buf[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		Pthread_mutex_unlock(&shared.mutex);
		*((int *)arg) += 1;
	}
}

void *consume(void *arg)
{
	int		i;
	
	for (i = 0; i < nitiems; i++)
	{
		if (shared.buf[i] != i)
			printf("buf[%d] = %d\n", i, shared.buf[i]);
	}
	return NULL;
}
