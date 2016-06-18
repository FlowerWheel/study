#include "myunp.h"

pid_t Fork()
{
	pid_t pid;

	if ((pid = fork()) == -1)
		err_sys("fork error");
	return pid;
}

void Ececl();

void Waitpid(pid_t pid, int *status, int options)
{
	if (waitpid(pid, status, options) == -1)
		err_sys("waitpid error");
}
