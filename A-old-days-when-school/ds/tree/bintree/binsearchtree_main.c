#include "binsearchtree.h"
#include "lueap.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print(__BTElemType x)
{
	printf("%d\t", x);
}

int main (void)
{
	BSTree	BST;
	int		isempty;
	int		dep;
	int		i;
	
	InitBSTree(&BST);
	
	isempty = IsEmptyBSTree(BST);
	printf("empty ? %d\n", isempty);

	dep = DepBSTree(BST);
	printf("%d\n", dep);

	for (i = 1; i < 30; i++)
		InsertBSTree(&BST, i);

	dep = DepBSTree(BST);
	printf("%d\n", dep);

	PreTraverseBinTree(BST, print);
	printf("\n");

	DestoryBSTree(&BST);
	return 0;
}
