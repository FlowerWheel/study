#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>

int main (int argc, char **argv)
{
	struct passwd	*ptrpw;

	setpwent();
	while ((ptrpw = getpwent()) != NULL)
	{
		printf("pw_name:%s\t", ptrpw->pw_name);
		printf("pw_passwd:%s\t", ptrpw->pw_passwd);
		printf("pw_uid:%d\t", ptrpw->pw_uid);
		printf("pw_gid:%d\t", ptrpw->pw_gid);
		printf("pw_gecos:%s\t", ptrpw->pw_gecos);
		printf("pw_dir:%s\t", ptrpw->pw_dir);
		printf("pw_shell:%s\t", ptrpw->pw_shell);
		printf("\n");
	}
	endpwent();
	return 0;
}
