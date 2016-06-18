#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "factorial.h"


#define		M_LENTH	1000000



int main (int argc, char **argv)
{
	char		multiplicand[M_LENTH];
	char		multiplier[M_LENTH];
	int			i;
	int			max;

	bzero(multiplicand, sizeof(multiplicand));
	multiplicand[0] = 1;
	
	printf("please input a number:");
	scanf("%d", &max);

	for(i = 2; i <= max; i++)
	{
		bzero(multiplier, sizeof(multiplier));
		sscanf(i, "%s", multiplier);
		multi(multiplicand, multiplier);
	}
	return 0;
}
