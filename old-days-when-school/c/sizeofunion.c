#include <stdio.h>

int main(int argc, char **argv)
{
	union{
		char str[10];
		double d;
	} u;

	printf ("%d\n", sizeof(u));
	return 0;
}
