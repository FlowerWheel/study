#include "lueap.h"
#include "bitmap.h"

int main (void)
{
	printf("hello world!\n");
	errno = EINVAL;
	err_sys("error");
	return 0;
}

