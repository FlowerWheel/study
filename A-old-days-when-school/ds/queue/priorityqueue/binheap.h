#ifndef _BINHEAP_H_
#define _BINHEAP_H_

#include "lueap.h"

struct	HeapStruct;
typedef	struct HeapStruct *PriorityQueue; 
typedef int	ElemType;

PriorityQueue InitPQ(int MaxSize);
PriorityQueue BuildHeap(ElemType arr[], int n);
void DestoryPQ(PriorityQueue *PQ);
void MakeEmptyPQ(PriorityQueue PQ);
void InsertPQ(PriorityQueue PQ, ElemType x);
ElemType DeleteMinPQ(PriorityQueue PQ);
ElemType FindMinPQ(PriorityQueue PQ);
int IsEmptyPQ(PriorityQueue PQ);
int IsFullPQ(PriorityQueue PQ);


#endif /*_BINHEAP_H_*/

#define MINSIZE	30

struct HeapStruct {
	int			capacity;
	int			size;
	ElemType	*base;
};
