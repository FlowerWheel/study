#ifndef  BITMAP_H
#define  BITMAP_H

#include "lueap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define MAXNUMOFBC 10000000

int BitContainer[1 + MAXNUMOFBC/BITSPERWORD];
void SetBit (int i) {        BitContainer[i>>SHIFT] |=  (1<<(i & MASK)); }
int  GetBit (int i) { return BitContainer[i>>SHIFT] &   (1<<(i & MASK)); }
void ClrBit (int i) {        BitContainer[i>>SHIFT] &= ~(1<<(i & MASK)); }


typedef struct BitMap{
	int		max;
	int		size;
	int		*base;
}BitMap, BitSet;

#define GETBMMAX(BM) (BM.max)
#define GETBMSIZE(BM) (BM.size)

void InitBM(BitMap *BM, int max)
{
	BM->max = max;
	BM->size = max / BITSPERWORD + 1;
	if ((BM->base = calloc(BM->size, sizeof(int))) == NULL)
		err_sys("calloc error");
}
int SetBitBM(BitMap *BM, int i)
{
	if (i > BM->max || i < 1)
	{
		err_msg("%d is too greater", i);
		return -1;
	}
	else 
	{
		BM->base[i >> SHIFT] |= (1 << (i & MASK));
		return 0;
	}
}
void SetBitBMAll(BitMap *BM)
{
	memset(BM->base, -1, BM->size * sizeof(BM->base));
}
int  GetBitBM(BitMap *BM, int i)
{
	if (i > BM->max || i < 1)
	{
		err_msg("%d is too greater", i);
		return -1;
	}
	return ( (BM->base[i >> SHIFT] & (1 << (i & MASK))) ? 1 : 0);
}
int ClrBitBM(BitMap *BM, int i)
{
	if (i > BM->max || i < 1)
	{
		err_msg("%d is too greater", i);
		return -1;
	}
	else
   	{
		BM->base[i >> SHIFT] &= ~(1 << (i & MASK));
		return 0;
	}
}
void ClrBitBMAll(BitMap *BM)
{
	memset(BM->base, 0, BM->size * sizeof(BM->base));
}
void TraverseBM(BitMap *BM)
{
	int		i, status;
	int		len = 1;
	for (i = 1; i <= BM->max; i++)
	{
		status = GetBitBM(BM, i);
		if (status == -1)
			err_quit("GetBitBM error");
		if (status)
		{
			if (len > 10)
			{
				printf("\n");
				len = 1;
			}
			len++;
			printf("%d ", i);
		}
	}
}
void DestoryBM(BitMap *BM)
{
	if (BM->base != NULL)
	{
		free(BM->base);
		BM->max = 0;
		BM->size = 0;
	}
}

BitMap MakePrimeTable(int N)
{
	BitMap		bm;
	int			i, j;
	int			sqrtn;

	InitBM(&bm, N);
	SetBitBMAll(&bm);
	sqrtn = (int)sqrt(N);
	ClrBitBM(&bm, 1);
		
	for (i = 2; i <= sqrtn; i++)
	{
		if (!GetBitBM(&bm, i))
			continue;
		for (j = 2 * i; j <= N; j += i)
			ClrBitBM(&bm, j);
	}
	return bm;
}

int PowerMod(int a, int b, int c)
{ 
	int ans = 1;
   	a = a % c; 
	while(b>0)
	{    
		if(b % 2 == 1)
			ans = (ans * a) % c; 
		b = b/2;  
		a = (a * a) % c;  
	} 
	return ans; 
}
unsigned long long QuickPower(unsigned long long a, unsigned long long b)
{ 
	unsigned long long ans = 1;
	while(b)
	{    
		if (b & 1)
			ans *= a; 
		b >>= 1;
		a *= a;  
	} 
	return ans; 
}

#endif  /*BITMAP_H*/
