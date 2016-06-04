#ifndef  SORT_H
#define  SORT_H

typedef int compare(const void *key1, const void *key2);

/*O(n) ~ O(n^2)*/
int	InsertSort(void *data, int size, int esize, compare *cmpf);

int QuickSort(void *data, int size, int esize, int i, int k, compare *cmpf);

int MergeSort(void *data, int size, int esize, int i, int k, compare *cmpt);

#endif  /*SORT_H*/
