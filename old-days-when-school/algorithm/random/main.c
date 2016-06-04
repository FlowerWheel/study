#include	"random.h"
#include	<stdio.h>
#include	<time.h>


int main (void)
{
	double	randnum = -1;

	Srand(time(NULL) << 10);
	randnum = Random1();
	printf("random = %f\n", randnum);
	return 0;
}
