#include "binheap.h"

#define N 20 

int main (void)
{
	int		i;
	ElemType a[N];

	PriorityQueue h;
	PriorityQueue p;

	h = InitPQ(100);
	printf("IsEmptyPQ ? %d\n", IsEmptyPQ(h));
	printf("IsFullPQ  ? %d\n", IsFullPQ(h));

	for (i = 1; i < 60; i++)
		InsertPQ(h, i);
	printf("IsEmptyPQ ? %d\n", IsEmptyPQ(h));

	printf("MIN = %d\n", FindMinPQ(h));
	for (i = 1; i < 60; i++)
		printf("%d ", DeleteMinPQ(h));
	printf("\n");

	printf("MIN = %d\n", FindMinPQ(h));
	DestoryPQ(&h);


	for (i = 1; i < N; i++)
		a[i] = N - i;

	p = BuildHeap(a, N);

	printf("MIN = %d\n", FindMinPQ(p));

	for (i = 1; i < N; i++)
		printf("%d ", DeleteMinPQ(p));
	printf("\n");

	printf("MIN = %d\n", FindMinPQ(p));

	DestoryPQ(&p);

	return 0;
}
