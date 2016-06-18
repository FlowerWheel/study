#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

#define MAXNITEM		1000000
#define MAXNTHREADS		100

int		nitiems;
int		buf[MAXNITEM];
int		who[MAXNITEM];

struct {
	pthread_mutex_t		mutex;
	int		nput;
	int		nval;
} put = {
	PTHREAD_MUTEX_INITIALIZER
};

struct {
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	int					nready;
} nready = {
	PTHREAD_MUTEX_INITIALIZER, 
	PTHREAD_COND_INITIALIZER
};

void	*produce(void *), *consume(void *);

int main (int argc, char **argv)
{
	int			sum;
	int			i, nthreads, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("usage : %s <#item> <#threads>", argv[0]);

	nitiems = min(atoi(argv[1]), MAXNITEM);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

//	Set_concurrency(nthreads);
//	pthread_setconcurrency(nthreads);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_consume, NULL, consume, NULL);

	for (i = 0; i < nthreads; i++)
	{
		Pthread_join(tid_produce[i], NULL);
		printf("cout[%d] = %d\n", i, count[i]);
	}

	Pthread_join(tid_consume, NULL);

	sum = 0;
	for (i = 0; i < nthreads; i++)
		sum += count[i];
	printf("sum = %d\n", sum);

	for (i = 0; i < nitiems; i++)
		printf("%d\n", who[i]);
	return 0;
}

void *produce(void *arg)
{
	for ( ; ; )
	{
		Pthread_mutex_lock(&put.mutex);
		if (put.nput >= nitiems)
		{
			Pthread_mutex_unlock(&put.mutex);
			return NULL;
		}	
		buf[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		who[put.nput] = pthread_self();
		Pthread_mutex_unlock(&put.mutex);

		Pthread_mutex_lock(&nready.mutex);
		if (nready.nready == 0)
			Pthread_cond_signal(&nready.cond);
		nready.nready++;
		Pthread_mutex_unlock(&nready.mutex);

		*((int *)arg) += 1;
	}
}

void *consume(void *arg)
{
	int		i;
	
	for (i = 0; i < nitiems; i++)
	{
		Pthread_mutex_lock(&nready.mutex);
		while (nready.nready == 0)	
			Pthread_cond_wait(&nready.cond, &nready.mutex);
		nready.nready--;
		Pthread_mutex_unlock(&nready.mutex);

		if (buf[i] != i)
			printf("buf[%d] = %d\n", i, buf[i]);
	}
	return NULL;
}
