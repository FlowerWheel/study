#include "type.h"
#include "bintree.h"
#include "stack.h"
#include "queue.h"
#include "lueap.h"
#include <stdio.h>


void print(char ch)
{
	printf("%c ", ch);
}

int main(int argc, char **argv)
{
	BinTree		T, tt;
	Stack		S;
	int			empty;
	int			dep;

	/***************Test Stack is work Ok
	*/	
	InitStack(&S);
	empty = IsEmptyStack(S);
	printf("IsEmptyStack : %d\n", empty);
	Push(T, &S);
	empty = IsEmptyStack(S);
	printf("IsEmptyStack : %d\n", empty);
	tt = Top(S);
	printf("%p\n", tt);
	printf("%p\n", T);
	Pop(&S);
	empty = IsEmptyStack(S);
	printf("IsEmptyStack : %d\n", empty);
	DestoryStack(&S);
	/**/

	InitBinTree(&T);
	
	empty = IsEmptyBinTree(T);
	printf("IsEmptyBinTree : %d\n", empty);

	dep = DepBinTree(T);
	printf("DepBinTree : %d\n", dep);

	PreCreateBinTree(&T);

	empty = IsEmptyBinTree(T);
	printf("IsEmptyBinTree : %d\n", empty);

	dep = DepBinTree(T);
	printf("DepBinTree : %d\n", dep);

	PreTraverseBinTree(T, print);
	printf("\n");
	InTraverseBinTree(T, print);
	printf("\n");
	PostTraverseBinTree(T, print);
	printf("\n");

	nonRecursivePreTraverseBinTree(T, print);
	printf("\n");

	nonRecursiveInTraverseBinTree(T, print);
	printf("\n");

	nonRecursivePostTraverseBinTree(T, print);
	printf("\n");

	LevelTraverseBinTree(T, print);

	printf("\n");
	DestoryBinTree(&T);

	return 0;
}
