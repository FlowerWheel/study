#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

//extern char a[];
//extern char *a;   //error
//char a[100];

/*
int main (void)
{
	int		a[5] = {1, 2, 3, 4};
//	char	b[5] = {'A', 'B', 'C', 'D', 'E'};
//	int		*ptr = (int *) (&a + 1);

//	printf ("%d %d\n", *(a + 1), *(ptr - 1));
//	printf ("a = %p  &a = %p\n", a, &a);

//	char (*p3)[8] = &b;
//	char (*p4)[8] = b;

//	printf ("%c %c\n", b, &b);
//	printf ("%c %c\n", p3, p4);

	int *ptr5 = (int *) (&a + 1);
	int *ptr6 = (int *) ((int)a + 1);

	printf("%d %d\n", ptr5[-1], *ptr6);
  	return 0;
}
*/
int main(int argc, char * argv[])
{

	int a [3][2]={(0, 1), (2, 3), (4, 5)};
	int *p;
	p=a [0];
	printf("%d", p[0]);

	return 0;
}
