#include <stdio.h>
#include <stdlib.h>

int main ( )
{
	printf( "Press any key to clear screen.\n");
	getchar();
	printf( "\033[H\033[2J"); /* ANSI驱动程序 */
	getchar();
	return EXIT_SUCCESS;
}
