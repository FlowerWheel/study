#include "avltree.h"
#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print(AvlElemType e, int height)
{
	printf("%d(%d)\t", e, height);
}

int main (void)
{
	AvlTree		avl;
	int			empty;
	int			i;
	int			dep;

	InitAVL(&avl);

	empty = IsEmptyAVL(avl);

	dep = DepAVL(avl);
	printf("%d\n", dep);

	printf("empty = %d\n", empty);

	for (i = 1; i <= 6; i++)
		InsertAVL(&avl, i);

	empty = IsEmptyAVL(avl);
	printf("empty = %d\n", empty);

	dep = DepAVL(avl);
	printf("%d\n", dep);

	PreTraverseAVL(avl, print);
	printf("\n");

	DeleteAVLNode(&avl, 6);

	PreTraverseAVL(avl, print);
	printf("\n");

	return 0;
}
