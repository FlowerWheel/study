#include "sort.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define N 1000000

int main (void)
{
	ElemType	Arr[N];
	int			i;

	for (i = 0; i < N; i++)
		Arr[i] = N - i;

	StuffleArr(Arr, N);

/*
	printf("before Sort:\n");
	for (i = 0; i < N; i++)
		printf("%d\t", Arr[i]);
	printf("\n");
*/
//	BubbleSort(Arr, N);
//	SelectSort(Arr, N);
//	InsertSort(Arr, N);
	ShellSort(Arr, N);
//	MergeSort(Arr, N);
//	QuickSort(Arr, N);
//	HeapSort(Arr, N);
/*
	printf("after Sort:\n");
	for (i = 0; i < N; i++)
		printf("%d\t", Arr[i]);
	printf("\n");
*/	
	return 0;
}
