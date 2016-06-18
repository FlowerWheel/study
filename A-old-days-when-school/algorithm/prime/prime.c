#include <math.h>
#include "lueap.h"
#include "bitmap.h"

//#define NSIZE	1024	

/**
 * @file prime.c
 * @brief make a prime table
 * @author Asins - asinsimple AT gmail DOT com
 * @version 1.0
 * @date 2013-09-21
 */


int main (void)
{
	BitMap	bm;
	int		i, j, k, minus = 1;
//	unsigned long long int ans;

	unsigned long long  NSIZE = QuickPower(2, 63);
	printf("NSIZE = %lld\n", NSIZE);

	bm = MakePrimeTable(10000000000);
	TraverseBM(&bm);
//	printf("\n");
/*

	for (j = 1; j < 64; j++)
	{
		ans = QuickPower(2, j);
		printf("[2^%d = %lld]  ", j, ans);
	}
	printf("\n");
*/
/*
	for (k = 1; k < NSIZE; )
	{
		for (i = k; i < NSIZE; i++)
			if (GetBitBM(&bm, i))
				break;
		for (j = i + 1; j < NSIZE; j++)
			if (GetBitBM(&bm, j))
				break;
		if (j - i == 2)
			printf ("[%d %d]\n", i, j);
		k = j;
	}
*/
	return 0;
}
