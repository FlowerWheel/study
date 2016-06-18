#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>

int main (int argc, char **argv)
{
	struct group	*ptrgrp;
	char			**ptrmem;
	setgrent();
	while ((ptrgrp = getgrent()) != NULL)
	{
		printf("%s: ", ptrgrp->gr_name);
		printf("%s: ", ptrgrp->gr_passwd);
		printf("%d ", ptrgrp->gr_gid);
		for(ptrmem = ptrgrp->gr_mem; *ptrmem != NULL; ptrmem++)
			printf("%s ", *ptrmem);
		printf("\n");
	}
	return 0;
}
