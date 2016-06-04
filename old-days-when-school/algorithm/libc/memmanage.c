// some functions for the memery manage in this file
#include "lueap.h"

void *Malloc(size_t size)
{
	void *pmalloc;
	
	if ((pmalloc = malloc(size)) == NULL)	
		err_sys("malloc error");
	return pmalloc;
}

void Free(void *ptr)
{
	free(ptr);
}

void *Calloc(size_t nmemb, size_t size)
{
	void *pcalloc;
	
	if ((pcalloc = calloc(nmemb, size)) == NULL)
		err_sys("calloc error");
	return pcalloc;
}

void *Realloc(void *ptr, size_t size)
{
	void *prealloc;

	if ((prealloc = realloc(ptr, size)) == NULL)
		err_sys("realloc error");
	return prealloc;
}
