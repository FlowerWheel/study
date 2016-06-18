#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	int		T = 0;
	switch (!!T)
	{
		case 0:
			printf("in case 0\n");
			break;
		case 1:
			printf("in case 1\n");
			break;
	}
	printf("%d\n", !!T);
	return 0;
}
