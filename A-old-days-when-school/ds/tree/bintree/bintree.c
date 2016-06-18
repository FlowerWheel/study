#include "bintree.h"
#include "type.h"
#include "lueap.h"

void InitBinTree(BT)
	BinTree *BT;
{
	*BT = NULL;
}
void MakeEmptyBinTree(BinTree *BT)
{
	if (*BT != NULL)
	{
		MakeEmptyBinTree(&(*BT)->left);
		MakeEmptyBinTree(&(*BT)->right);
		free(*BT);
	}
	*BT = NULL;
}
void DestoryBinTree(BT)
	BinTree *BT;
{
	if (*BT != NULL)
	{
		DestoryBinTree(&(*BT)->left);
		DestoryBinTree(&(*BT)->right);
		free(*BT);
	}
	*BT = NULL;
}
int	 IsEmptyBinTree(const BinTree BT)
{
	return (BT == NULL);
}
int	 DepBinTree(const BinTree BT)
{
	int leftDep, rightDep;

	leftDep = rightDep = -1;

	if (BT != NULL)
	{
		leftDep = DepBinTree(BT->left);
		rightDep = DepBinTree(BT->right);
	}
	return (leftDep >= rightDep ? ++leftDep : ++rightDep);
}
void PreCreateBinTree(BinTree *BT)
{
	BTElemType	ch;
	pBTNode pBTN;

	scanf("%c", &ch);
	if (ch != '#')
	{
		if ((pBTN = malloc(sizeof(BTNode))) == NULL)
		{
			perror("malloc error");
			exit(EXIT_FAILURE);
		}
		*BT = pBTN;
		pBTN->data = ch;
		PreCreateBinTree(&(*BT)->left);
		PreCreateBinTree(&(*BT)->right);
	}
	else
		*BT = NULL;
}
void PreTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	if(BT != NULL)
	{
		visit(BT->data);
		PreTraverseBinTree(BT->left, visit);
		PreTraverseBinTree(BT->right, visit);
	}
}
void InTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	if(BT != NULL)
	{
		InTraverseBinTree(BT->left, visit);
		visit(BT->data);
		InTraverseBinTree(BT->right, visit);
	}
}
void PostTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	if(BT != NULL)
	{
		PostTraverseBinTree(BT->left, visit);
		PostTraverseBinTree(BT->right, visit);
		visit(BT->data);
	}
}
void nonRecursivePreTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	pBTNode		pBTN = BT;
	pBTNode		top;
	Stack		s_pBTN;

	/*
	InitStack(&s_pBTN);
	if (pBTN)
		Push(pBTN, &s_pBTN);
	while (!IsEmptyStack(s_pBTN))
	{
		while ((top = Top(s_pBTN)), top)
		{
			visit(top->data);
			Push(top->left, &s_pBTN);
		}
		Pop(&s_pBTN);
		if (!IsEmptyStack(s_pBTN))
		{
			top = Top(s_pBTN);
			Pop(&s_pBTN);
			Push(top->right, &s_pBTN);
		}
	}
	DestoryStack(&s_pBTN);
	*/

	InitStack(&s_pBTN);
	if (pBTN)
		Push(pBTN, &s_pBTN);
	while (!IsEmptyStack(s_pBTN))
	{
		top = Top(s_pBTN);
		visit(top->data);
		Pop(&s_pBTN);
		if (top->right != NULL)
			Push(top->right, &s_pBTN);
		if (top->left != NULL)
			Push(top->left, &s_pBTN);
	}
	DestoryStack(&s_pBTN);


	/*
	for ( ; ; )
	{
		if (pBTN)
			visit(pBTN->data);

		while (pBTN->left)
		{
			visit(pBTN->data);
			Push(pBTN, &s_pBTN);
			pBTN = pBTN->left;
		}

		top = Top(s_pBTN);

		if (IsEmptyStack(s_pBTN))
		{
			if (top->right)
			{
				pBTN = top->right;
				Pop(&s_pBTN);
				continue;
			}
			else
			{
				while (!top->right)
				{
					Pop(&s_pBTN);
					top = Top(s_pBTN);
				}
				pBTN = top->right;
				Pop(&s_pBTN);
				continue;
			}
		}
		else
			break;
	}
	*/
}
void nonRecursiveInTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	pBTNode		pBTN = BT;
	pBTNode		top;
	Stack		s_pBTN;
	InitStack(&s_pBTN);
	if (pBTN)
		Push(pBTN, &s_pBTN);
	while (!IsEmptyStack(s_pBTN))
	{
		while ((top = Top(s_pBTN)), top)
		{
			Push(top->left, &s_pBTN);
		}
		Pop(&s_pBTN);
		if (!IsEmptyStack(s_pBTN))
		{
			top = Top(s_pBTN);
			visit(top->data);
			Pop(&s_pBTN);
			Push(top->right, &s_pBTN);
		}
	}
	DestoryStack(&s_pBTN);

/*
	InitStack(&s_pBTN);
	if (pBTN)
		Push(pBTN, &s_pBTN);
	while (!IsEmptyStack(s_pBTN))
	{
		top = Top(s_pBTN);
		Pop(&s_pBTN);
		if (top->right != NULL)
			Push(top->right, &s_pBTN);
		visit(top->data);
		if (top->left != NULL)
			Push(top->left, &s_pBTN);
	}
	DestoryStack(&s_pBTN);
*/
}
void nonRecursivePostTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	pBTNode		pBTN = BT;
	pBTNode		top_a, top_b;
	Stack		s_a, s_b;

	InitStack(&s_a);
	InitStack(&s_b);
	if (pBTN)
		Push(pBTN, &s_a);
	while (!IsEmptyStack(s_a))
	{
		while (top_a = Top(s_a), top_a)
			Push(top_a->left, &s_a);
		Pop(&s_a);
		if (!IsEmptyStack(s_b))
		{
			top_a = Top(s_a);
			top_b = Top(s_b);
			if (top_a == top_b)
			{
				visit(top_b->data);
				Pop(&s_a); 
				Pop(&s_b);
				Push(NULL, &s_a);
			}
			else 
			{
				visit(top_a->data);
				Pop(&s_a);
				Push(top_a->right, &s_a);
			}
		}
		else if(!IsEmptyStack(s_a)) 
		{
			top_a = Top(s_a);
			if (top_a->right)
			{
				Push(top_a, &s_b);
				Push(top_a->right, &s_a);
			}
			else 
			{
				visit(top_a->data);
				Pop(&s_a);
				Push(top_a->right, &s_a);
			}
		}
		else
			;
	}
	DestoryStack(&s_a);
	DestoryStack(&s_b);
}

void LevelTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e))
{
	Queue	q_pBTN;
	pBTNode pBTN = BT;

	InitQueue(&q_pBTN);
	if (pBTN)
		EnQueue(pBTN, &q_pBTN);
	while (!IsEmptyQueue(q_pBTN))
	{
		pBTN = Front(q_pBTN);
		visit(pBTN->data);
		DeQueue(&q_pBTN);
		if (pBTN->left)
			EnQueue(pBTN->left, &q_pBTN);
		if (pBTN->right)
			EnQueue(pBTN->right, &q_pBTN);
	}
	DestoryQueue(&q_pBTN);
}
