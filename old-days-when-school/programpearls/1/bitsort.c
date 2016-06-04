/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsort.c -- bitmap sort from Column 1
 *   Sort distinct integers in the range [0..N-1]
 */

#include <stdio.h>
#include <stdlib.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000

int a[1 + N/BITSPERWORD];

void set (int i) {        a[i>>SHIFT] |=  (1<<(i & MASK)); }
void clr (int i) {        a[i>>SHIFT] &= ~(1<<(i & MASK)); }
int  test(int i) { return a[i>>SHIFT] &   (1<<(i & MASK)); }


int main(int argc, char **argv)
{	
	FILE	*fp;
	int		i, n;
	int		data;

	if ((fp = fopen(argv[1], "r+")) == NULL)
		perror("fopen error!");

	for (i = 1; i < N; i++)
	{
		n = fread(&data, sizeof(int), 1, fp);
		if (n == -1)
			perror("fread error");
		set(data);
	}

	if ( n == -1 )	perror("fread error");

	fseek(fp, 0, SEEK_SET);	
	for (i = 1; i < N; i++)
	{
		if (test(i))
			if (fwrite(&i, sizeof(int), 1, fp) != 1)
				perror("fwrite error");
	}
	return 0;
}
