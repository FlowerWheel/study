#include "search.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	int	a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int pos = BinSearch(a, 0, 10, 1);

	printf("pos = %d\n", pos);

	pos = BinSearch(a, 0, 10, 9);

	printf("pos = %d\n", pos);

	return 0;
}
