#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

char *TestFileType(struct stat *buf)
{
	char	*ptr;

	if (S_ISREG(buf->st_mode))
		ptr = "regular";
	else if (S_ISDIR(buf->st_mode))
		ptr = "directory";
	else if (S_ISCHR(buf->st_mode))
		ptr = "character";
	else if (S_ISBLK(buf->st_mode))
		ptr = "block";
	else if (S_ISFIFO(buf->st_mode))
		ptr = "fifo";
	else if (S_ISLNK(buf->st_mode))
		ptr = "link";
	else if(S_ISSOCK(buf->st_mode))
		ptr = "sock";
	else ptr = "unknown mode";
		return ptr;

}
char *JudgeFileType(struct stat *buf)
{
	char	*ptr;
	
	switch(buf->st_mode & S_IFMT)
	{
		case S_IFREG:
			ptr = "regular";
			break;
		case S_IFDIR:
			ptr = "directory";
			break;
		case S_IFCHR:
			ptr = "character";
			break;
		case S_IFBLK:
			ptr = "block";
			break;
		case S_IFIFO:
			ptr = "fifo";
			break;
		case S_IFLNK:
			ptr = "link";
			break;
		case S_IFSOCK:
			ptr = "socket";
			break;
		default:
			ptr = "unknown mode";
	}
	return ptr;

}

int main (int argc, char **argv)
{
	int		i;
	char	*ptr;
	struct stat	buf;

	for(i = 1; i < argc; i++)
	{
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) == -1)
		{
			perror("lstat error");
			continue;
		}
		ptr = TestFileType(&buf);
//		ptr = JudgeFileType(&buf);
		printf("%s\n", ptr);
	}
	return 0;
}
