#include "lueap.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <pthread.h>

int reg, dir, chr, blk, fifo, lnk, sock, unk, total;

void travedir(char *pathname);

int main (int argc, char **argv)
{
	unsigned	pathmax;
	char		*path;

	if (argc != 2)
		err_quit("usage : %s <pathname>", argv[0]);

	if ((pathmax = pathconf("/", _PC_PATH_MAX)) == -1)
		err_sys("pathname error");

	path = Malloc(pathmax);

	strncpy(path, argv[1], pathmax);
	
	travedir(path);

	printf("reg = %d\n", reg);
	printf("dir = %d\n", dir);
	printf("chr = %d\n", chr);
	printf("blk = %d\n", blk);
	printf("fif = %d\n", fifo);
	printf("lnk = %d\n", lnk);
	printf("sck = %d\n", sock);
	printf("unk = %d\n", unk);
	printf("total = %d\n", total);

	return 0;
}

void count(struct stat *buf)
{
	total++;
	if (S_ISREG(buf->st_mode))
		reg++;
	else if (S_ISDIR(buf->st_mode))
		dir++;
	else if (S_ISCHR(buf->st_mode))
		chr++;
	else if (S_ISBLK(buf->st_mode))
		blk++;
	else if (S_ISFIFO(buf->st_mode))
		fifo++;
	else if (S_ISLNK(buf->st_mode))
		lnk++;
	else if(S_ISSOCK(buf->st_mode))
		sock++;
	else 
		unk++;
}

void travedir(char *pathname)
{
	char	*ptr = pathname + strlen(pathname);
	struct stat buf;
	DIR		*dirp;
	struct dirent *direntp;

	lstat(pathname, &buf);

	count(&buf);

	if (!S_ISDIR(buf.st_mode))
		printf("%s\n", pathname);
	else{
		*ptr++ = '/';
		*ptr = 0;
		dir++;
		if ((dirp = opendir(pathname)) == NULL)
			err_quit("opendir error %s", pathname);
		while ((direntp = readdir(dirp)) != NULL)
		{
			if ((strcmp(direntp->d_name, ".") == 0) ||
					(strcmp(direntp->d_name, "..") == 0))
				continue;
			strcpy(ptr, direntp->d_name);
			travedir(pathname);
		}
		ptr[-1] = 0;
		if (closedir(dirp) == -1)
			err_ret("can not close dir %s", pathname);
	}
}
