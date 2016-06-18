#ifndef  SEARCH_H
#define  SEARCH_H

typedef int compare(const void *key1, const void *key2);

int BinSearch(void *sorted, int size, void *target, int esize, compare *cmpf);


#endif  /*SEARCH_H*/
