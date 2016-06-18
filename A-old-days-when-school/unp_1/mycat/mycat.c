#include "myunp.h"
#include "header.h"

int main(int argc, char **argv)
{
	int fd, n;
	char buf[BUFSIZ];

	if (argc != 2)
		err_quit("usage: mycat <pathname>");

	if ((fd = my_open(argv[1], O_RDONLY)) < 0)
		err_sys("can not open %s", argv[1]);
	while ((n = Read(fd, buf, BUFSIZ)) > 0)
		Write(STDOUT_FILENO, buf, n);
	exit(0);
}
