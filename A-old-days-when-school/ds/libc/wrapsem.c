#include "lueap.h"
#include <stdarg.h>
#include <semaphore.h>

/*
sem_t *Sem_open(const char *name, int flags, ...)
{
	va_list		ap;

	va_start(ap, flags);
	if (sem_open(name, flags, ap) == SEM_FAILED)
		err_sys("sem_open error");
	va_end(ap);
}

void Sem_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		err_sys("sem_close error");
}

void Sem_unlink(const char *name)
{
	if (sem_unlink(name) == -1)
		err_sys("sem_close error");
}
int Sem_getvalue(sem_t *sem, int *valp)
{
	if (Sem_getvalue(sem, valp) == -1)
		err_sys("sem_getvalue");
}
int Sem_wait(sem_t *sem)
{
	if (sem_wait(sem) == -1)
		err_sys("sem_wait error");
}

int Sem_trywait(sem_t *sem)
{
	if (sem_trywait(sem) == -1)
		err_sys("sem_trywait error");
}

int Sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
		error("sem_post error");
}
*/
