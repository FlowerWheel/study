#include "hash.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TABLESIZE 1007

int main (void)
{
	int		i;
//	position	pos;

	HashTable	ht;

	ht = InitTable(10);

	for (i = 100; i >=0 ; i -= 2)
		Insert(ht, i);

	TraverseTable(ht);

	for (i = 100; i >=0; i --)
		Retrieve(Find(ht, i));

	printf("\n");
	return 0;
}
