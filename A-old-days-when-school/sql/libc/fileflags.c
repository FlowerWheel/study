// undefined in lueap.h
#include "lueap.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define		ON	1
#define		OFF 0

void set_fl(int fd, int flags, int type)
{
	int		val;
	
	if ((val = fcntl(fd, F_GETFL, 0)) == -1)
		err_sys("fcntl F_GETFL error");

	if (type == ON)
		val |= flags;
	else if (type == OFF)
		val &= ~flags;
	else 
		err_quit("unknow type");

	if  (fcntl(fd, F_SETFL, val) == -1)
		err_sys("fcntl F_SETFL error");
}

void getfl(int fd)
{
	int		val;

	if ((val = fcntl(fd, F_GETFL, 0)) == -1)
		err_sys("fcntl F_GETFL error");

	switch (val & O_ACCMODE)
	{
		case O_RDONLY:

			break;
		case O_WRONLY:

			break;
		case O_RDWR:

			break;
		default:
			err_dump("unknow access mode");
	}
	
	if (val & O_APPEND)
		;
	if (val & O_NONBLOCK)
		;
#if defined (O_SYNC)
	if (val & O_SYNC)
		;
#endif
#if !defined (_POSIX_C_SOURCE) && defined (O_FSYNC)
	if (val & O_FSYNC)
		;
#endif
}
