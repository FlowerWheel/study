#include "lueap.h"

/*
int	 Ioctl(int d, int request, ...)
{
	int i;
	
	if ((i = ioctl(d, request, ...)) == -1)
		err_sys("ioctl error");
	return i;
}
*/

void Open()
{

}

void Close(int fd)
{
	if (close(fd) != 0)
		err_sys("close error");
}

ssize_t Read(int fd, void *buf, size_t count)
{
	ssize_t		n;
	if((n = read(fd, buf, count)) == -1)
		err_sys("read error");
	return n;
}

void Write(int fd, void *buf, size_t count)
{
	if (write(fd, buf, count) < count)
		err_sys("write error");
}

ssize_t readn(int fd, void *vptr, size_t n)
{
	ssize_t nread;
	size_t nleft = n;
	void *ptr = vptr;

	while(nleft > 0){
		if ((nread = read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;
			else 
				return -1;
		}else if(nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}
	
	return (n - nleft);
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
	ssize_t nwrite;
	size_t	nleft = n;
	char	*ptr;
	
	ptr = (void *)vptr;
	while(nleft > 0){
		if((nwrite = write(fd, ptr, nleft)) <= 0)
		{
			if(nwrite < 0 && errno == EINTR)
				nwrite = 0;
			else 
				return -1;
		}
		nleft -= nwrite;
		ptr += nwrite;
	}
	return (n - nleft);
}

ssize_t readline1(int fd, void *vptr, size_t linelen)
{
	ssize_t n, rc;
	char	c, *ptr;

	ptr = vptr;
	for(n = 1; n < linelen; n++)
	{
again:
		if((rc = read(fd, &c, 1)) == 1)
		{
			*ptr++ = c;
			if(c == '\n')
				break;
		}else if(rc == 0){
			*ptr = 0;
			return (n - 1);
		}else{
			if(errno == EINTR)
				goto again;
			return -1;
		}
	}
	*ptr = 0;
	printf("n = %d\n", n);
	return n;
}
