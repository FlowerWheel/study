/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsort.c -- bitmap sort from Column 1
 *   Sort distinct integers in the range [0..N-1]
 */

#include <stdio.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000
int a[1 + N/BITSPERWORD];

void set(int i) {        a[i>>SHIFT] |=  (1<<(i & MASK)); }
void clr(int i) {        a[i>>SHIFT] &= ~(1<<(i & MASK)); }
int  test(int i){ return a[i>>SHIFT] &   (1<<(i & MASK)); }

int main()
{	int i;
	for (i = 0; i < N; i++)
		clr(i);
/*	Replace above 2 lines with below 3 for word-parallel init
	int top = 1 + N/BITSPERWORD;
	for (i = 0; i < top; i++)
		a[i] = 0;
 */
	while (scanf("%d", &i) != EOF)
		set(i);
	for (i = 0; i < N; i++)
		if (test(i))
			printf("%d\n", i);
	return 0;
}



/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsortgen.c -- gen $1 distinct integers from U[0,$2) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 2000000
int x[MAXN];

int randint(int a, int b)  /* rand() a number from a to b */
{
	return a + (RAND_MAX * rand() + rand()) % (b + 1 - a);
}

int main(int argc, char *argv[])
{
	int i, k, n, t, p;
	srand((unsigned) time(NULL));
	k = atoi(argv[1]);
	n = atoi(argv[2]);
	for (i = 0; i < n; i++)
		x[i] = i;
	for (i = 0; i < k; i++) {
		p = randint(i, n-1);
		t = x[p]; x[p] = x[i]; x[i] = t;
		printf("%d\n", x[i]);
	}
	return 0;
}



/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* qsortints.c -- Sort input set of integers using qsort */

#include <stdio.h>
#include <stdlib.h>

int intcomp(int *x, int *y)
{  
   	return *x - *y;
}

int a[1000000];

int main()
{ 
  	int i, n=0;
    while (scanf("%d", &a[n]) != EOF)
        n++;
    qsort(a, n, sizeof(int), intcomp);
    for (i = 0; i < n; i++)
        printf("%d\n", a[i]);
    return 0;
}



/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* sortints.cpp -- Sort input set of integers using STL set */

#include <iostream>
#include <set>
using namespace std;

int main()
{	set<int> S;
	int i;
	set<int>::iterator j;
	while (cin >> i)
		S.insert(i);
 	for (j = S.begin(); j != S.end(); ++j)
		cout << *j << "\n";
	return 0;
}
