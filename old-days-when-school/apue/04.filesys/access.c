#include "lueap.h"

int main (int argc, char **argv)
{
	int		fd;
	if (argc != 2)
		err_quit("usage : %s <pathname>", argv[0]);

	if (access(argv[1], R_OK) == -1)
		err_ret("access error for %s", argv[1]);
	else 
		printf("access ok for %s\n", argv[1]);

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		err_ret("open error for %s", argv[1]);
	else 
		printf("open ok for %s\n", argv[1]);
	close(fd);
	return 0;
}
