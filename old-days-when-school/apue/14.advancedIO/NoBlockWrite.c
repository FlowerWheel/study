#include	"lueap.h"
#include	<error.h>
#include	<fcntl.h>

#define		BUF_SIZ		500000

char	buf[BUF_SIZ];

int main (void)
{
	int			ntowrite, nwrite;
	char		*ptr;
	int			i;

	for (i = 0; i < BUF_SIZ; ++i)
		buf[i] = i;

	/* fl_on(STDOUT_FILENO, O_NONBLOCK); */
	set_fl(STDOUT_FILENO, O_NONBLOCK, 1);

	ntowrite = BUF_SIZ;
	ptr = buf;
	while (ntowrite > 0)
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %s:%d\n", nwrite, strerror(errno), errno);

		if (nwrite > 0)
		{
			ptr += nwrite;
			ntowrite -=nwrite;
		}
	}

	/* fl_off(STDOUT_FILENO, O_NONBLOCK); */
	set_fl(STDOUT_FILENO, O_NONBLOCK, 0);

	return 0;
}
