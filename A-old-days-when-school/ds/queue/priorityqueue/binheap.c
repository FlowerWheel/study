#include "binheap.h"
#include "lueap.h"

PriorityQueue InitPQ(int MaxSize)
{
	PriorityQueue	H;
	
	if (MaxSize < MINSIZE)
		err_msg("MaxSize is too small");

	if ((H = malloc(sizeof(struct HeapStruct))) == NULL)
		err_sys("malloc error for H");

	if ((H->base = malloc(MaxSize * sizeof(ElemType))) == NULL)
		err_sys("malloc error for H->base");

	H->capacity = MaxSize;
	H->size = 0;

	return H;
}
void Swap(ElemType *a, ElemType *b)
{
	ElemType tmp=*a;*a=*b;*b=tmp;
}
void PerolateDown(ElemType arr[], int pos, int n)
{
	int		child;
	int		i;
	for (; pos > 0; pos--)
	{
		for (i = pos; 2 * i <= n; i = child)
		{
			child = i * 2;
			if (child != n &&
					arr[child + 1] < arr[child])
				child ++;
			if (arr[i] > arr[child])
				Swap(&arr[i], &arr[child]);
		}
	}
}
PriorityQueue BuildHeap(ElemType arr[], int n)
{
	int		i;
	PriorityQueue	H;

	for (i = n / 2; i > 0; i--)
		PerolateDown(arr, i, n);

	if ((H = malloc(sizeof(struct HeapStruct))) == NULL)
		err_sys("malloc error for H");

	if ((H->base = malloc(2 * n * sizeof(ElemType))) == NULL)
		err_sys("malloc error for H->base");

	H->capacity = 2 * n;
	H->size = n - 1;
	memcpy(H->base, arr, n * sizeof(ElemType));
	return H;

}
void DestoryPQ(PriorityQueue *PQ)
{
	if (*PQ == NULL)
		return ;
	free((*PQ)->base);
	free(*PQ);
	*PQ = NULL;
}
void MakeEmptyPQ(PriorityQueue PQ)
{
	if (PQ != NULL)
		PQ->size = 0;
	else 
		err_msg("PQ == NULL");
}
int IsEmptyPQ(PriorityQueue PQ)
{
	return ((PQ->size) ? 0 : 1 );
}
int IsFullPQ(PriorityQueue PQ)
{
	return (PQ->size == PQ->capacity);
}
void InsertPQ(PriorityQueue PQ, ElemType x)
{
	int		i;
	
	if (IsFullPQ(PQ))
		err_quit("PQ is full");
	for (i = ++PQ->size; i > 0 && x < PQ->base[i/2]; i /= 2)
		PQ->base[i] = PQ->base[i/2];
	PQ->base[i] = x;
}
ElemType DeleteMinPQ(PriorityQueue PQ)
{
	int			i, child;
	ElemType	MinElem, LastElem;

	if (IsEmptyPQ(PQ))
		err_quit("PQ is empty");
	MinElem = PQ->base[1];
	//printf("PQSIZE___1 = %d\n", PQ->size);
	LastElem = PQ->base[PQ->size--];
	//printf("PQSIZE___2 = %d\n", PQ->size);

	for (i = 1; i * 2 <= PQ->size; i = child)
	{
		child = i * 2;
		if (child != PQ->size &&
				PQ->base[child + 1] < PQ->base[child])
			child ++;
		if (LastElem > PQ->base[child])
			PQ->base[i] = PQ->base[child];
		else 
			break;
	}
	PQ->base[i] = LastElem;
	return MinElem;
}
ElemType FindMinPQ(PriorityQueue PQ)
{
	if (IsEmptyPQ(PQ))
		err_msg("PQ is empty");
//	printf("PQSIZE___3 = %d\n", PQ->size);
	return PQ->base[1];
}
