#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <shadow.h>

int main (int argc, char **argv)
{
	struct spwd		*ptrspw;

	setspent();
	while ((ptrspw = getspent()) != NULL)
	{
		printf("%s:", ptrspw->sp_namp);
		printf("%s:", ptrspw->sp_pwdp);
		printf("%ld:", ptrspw->sp_lstchg);
		printf("%ld:", ptrspw->sp_min);
		printf("%ld:", ptrspw->sp_max);
		printf("%ld:", ptrspw->sp_warn);
		printf("%ld:", ptrspw->sp_inact);
		printf("%ld:", ptrspw->sp_expire);
//		printf("%ld:", ptrspw->sp_flags);
		printf("\n");
	}
	endspent();
	return 0;
}
