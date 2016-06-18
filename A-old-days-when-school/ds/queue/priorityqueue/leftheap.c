#include "leftheap.h"
#include "lueap.h"

PriorityQueue InitLH(void);
{
	PriorityQueue LH == NULL;
	return LH;
}
ElemType FindMinLH(PriorityQueue LH)
{
	if (LH == NULL)
		err_msg("LH == NULL");
	else 
		return LH->data;
}
int	IsEmptyLH(PriorityQueue LH)
{
	return (LH == NULL);
}

static void SwapChildren(PriorityQueue LH)
{
	PriorityQueue tmp;
	tmp = LH->left;
	LH->left = LH->right;
	LH->right = tmp;
}
static PriorityQueue Merge1(PriorityQueue LH1, PriorityQueue LH2)
{
	if (LH1->left == NULL)
		LH1->left = LH2;
	else 
	{
		LH1->right = Merge(LH1->right, LH2);
		if (LH1->left->npl < LH1->right->npl)
			SwapChildren(LH1);
		LH1->npl = LH1->right->npl + 1;
	}
}
PriorityQueue MergeLH(PriorityQueue LH1, PriorityQueue LH2)
{
	if ( LH1 == NULL && LH2 == NULL)
		return NULL;
	else if ( LH1 == NULL)
		return LH2;
	else if ( LH2 == NULL)
		return LH1;
	else 
	{
		if (LH1->data < LH2->data)
			return Merge1(LH1, LH2);
		else 
			return Merge1(LH2, LH1);
	}
}

PriorityQueue Insert1LH(PriorityQueue LH, ElemType x)
{
	PriorityQueue SingleNode;
	if ((SingleNode = malloc(sizeof(struct TreeNode))) == NULL)
		err_sys("malloc error");
	else 
	{
		SingleNode->data = x;
		SingleNode->npl = 0;
		SingleNode->left = NULL;
		SingleNode->right = NULL;
		LH = Merge(SingleNode, LH);
	}
	return LH;
}
PriorityQueue DeleteMin1LH(PriorityQueue LH)
{
	PriorityQueue LeftChild, RightChild;

	if ( LH == NULL)
		err_msg("LH == NULL");
	LeftChild = LH->left;
	RightChild = LH->right;	
	return Merge(LeftChild, RightChild);
}
