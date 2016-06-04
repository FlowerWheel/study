#include "sort.h"
#include "lueap.h"
#include "bitmap.h"

#define ElemType int

static void Swap(ElemType *x, ElemType *y){ElemType tmp=*x; *x = *y; *y=tmp;}

void StuffleArr(ElemType A[],  int N)
{
	int     i,  j;
	srand(time(NULL));
	for(i = 0; i < N; i++)
	{
		j = rand() % N;
		Swap(&A[i], &A[j]);
	}   
}

void BubbleSort(ElemType A[], int N)
{
	int		i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N - i; j++)
			if (A[j] > A[j+1])
				Swap(&A[j], &A[j+1]);
}

void SelectSort(ElemType A[], int N)
{
	int		i, j;
	int		min_index;
	for (i = 0; i < N - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < N; j++)
			if (A[j] < A[min_index])
				min_index = j;
		Swap(&A[i], &A[min_index]);
	}
}

void InsertSort(ElemType A[], int N)
{
	int		j, p;
	ElemType	tmp;
	for (p = 1; p < N; p++)
	{
		tmp = A[p];
		for (j = p; j > 0 && tmp < A[j-1]; j--)
			A[j] = A[j-1];
		A[j] = tmp;
	}
}

static int PrePrime(BitMap bm, int N)
{
	int     i;  
	for (i = N - 1; i > 0; i--)
		if (GetBitBM(&bm, i)) 
			break;
	return i;
}
void ShellSort(ElemType A[], int N)
{
	int			i, j, Increment;
	ElemType	tmp;
	BitMap bm = MakePrimeTable(N/3);
//	SetBitBM(&bm, 1);
	Increment = PrePrime(bm, N/3);
//	for ( Increment = N / 2; Increment > 0; Increment /= 2)
	while (Increment > 1)
	{
		printf("%d\n", Increment);
		for (i = Increment; i < N; i++)
		{
			tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (tmp < A[ j - Increment ])
					A[j] = A[ j - Increment ];
				else
					break;
			A[ j ] = tmp;
		}
		Increment = PrePrime(bm, Increment/3);
	}
//	printf("1\n");
	InsertSort(A, N);
}

static void Merge(ElemType A[], ElemType TmpArr[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, ElemNum, TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	ElemNum = RightEnd - Lpos + 1;
/*
	while (Lpos <= LeftEnd && Rpos <= RightEnd)
		if (A[Lpos] <= A[Rpos])
			Swap(&A[Lpos++], &A[Rpos++]);
*/

	while (Lpos <= LeftEnd && Rpos <= RightEnd)
		if (A[Lpos] <= A[Rpos])
			TmpArr[TmpPos++] = A[Lpos++];
		else
			TmpArr[TmpPos++] = A[Rpos++];

	while (Lpos <= LeftEnd)
		TmpArr[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpArr[TmpPos++] = A[Rpos++];

	for (i = 0; i < ElemNum; i++, RightEnd--)
		A[RightEnd] = TmpArr[RightEnd];

}
static void MSort(ElemType A[], ElemType TmpArr[], int left, int right)
{
	int		center;
	if (left < right)
	{
		center = (left + right) / 2;
		MSort(A, TmpArr, left, center);
		MSort(A, TmpArr, center + 1, right);
		Merge(A, TmpArr, left, center + 1, right);
	}
}
void MergeSort(ElemType A[], int N)
{
	ElemType	tmparr[N]; 
	MSort(A, tmparr, 0, N - 1);
}

static ElemType Median3(ElemType A[], int left, int right)
{
	int center = (left + right) / 2;

	if (A[left] > A[center])
		Swap(&A[left], &A[center]);
	if (A[left] > A[right])
		Swap(&A[left], &A[right]);
	if (A[center] > A[right])
		Swap(&A[center], &A[right]);
	Swap (&A[center], &A[right - 1]);
	return A[right - 1];
}
static void QSort(ElemType A[], int left, int right)
{
	int			i, j;
	ElemType	Pivot;
#define CutOff ( 3 )
	if (left + CutOff <= right)
	{
		Pivot = Median3(A, left, right);
		i = left; j = right - 1;
		while (1)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j) Swap(&A[i], &A[j]);
			else break;
		}
		Swap(&A[i], &A[right - 1]);
		QSort(A, left, i - 1);
		QSort(A, i + 1, right);
	}
	else 
		InsertSort(A+left, right - left + 1);
}
void QuickSort(ElemType A[], int N)
{
	QSort(A, 0, N - 1);
}

static void PercDown(ElemType A[], int i, int N)
{
	int			child;
	ElemType	tmp;
#define LeftChild(i) (2 * (i) + 1)
	for (tmp = A[i]; LeftChild(i) < N; i = child)
	{
		child = LeftChild(i);
		if (child != N-1 && A[child + 1] > A[child])
			child ++;
		if (tmp < A[child])
			A[i] = A[child];
		else 
			break;
	}
	A[i] = tmp;
}
void HeapSort(ElemType A[], int N)
{
	int		i;
	for (i = N/2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N-1; i > 0; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}
