#include "binsearchtree.h"
#include "lueap.h"
#include "bintree.h"

void InsertBSTree(BSTree *BST, BSTElemType x)
{
	if (*BST == NULL)
	{
		if ((*BST = malloc(sizeof (BSNode))) == NULL)
			err_sys("malloc error in func InsertBSTree");
		(*BST)->data = x;
		(*BST)->left = NULL;
		(*BST)->right = NULL;

	}
	else if (x < (*BST)->data)
	{
		InsertBSTree(&(*BST)->left, x);
	}
	else if (x > (*BST)->data)
	{
		InsertBSTree(&(*BST)->right, x);
	}
	else if (x == (*BST)->data)
	{
		err_msg("The element %d already exist", x);
	}
}
void CreatBSTree(BSTree *BST)
{
	int		num;
	
	if (!IsEmptyBSTree(*BST))
		err_quit("The tree isn't empty");
	while (scanf("%d", &num) != EOF)
	{
		InsertBSTree(BST, num);
	}
}

pBSNode Find(BSTree BST, BSTElemType x)
{
	if (BST == NULL)
		return NULL;

	if (x < BST->data)
		return Find(BST->left, x);
	else if (x > BST->data)
		return Find(BST->right, x);
	else 
		return BST;
}
pBSNode FindMin(BSTree BST)
{
	pBSNode		pBSN = BST;

	if (BST == NULL)
	{
		err_msg("Find Max in empty BSTree");
		return NULL;
	}
	while (pBSN->left)
		pBSN = pBSN->left;
	return pBSN;
}
pBSNode FindMax(BSTree BST)
{
	pBSNode		pBSN = BST;

	if (BST == NULL)
	{
		err_msg("Find Max in empty BSTree");
		return NULL;
	}
	while (pBSN->right)
		pBSN = pBSN->right;
	return pBSN;
}

BSTElemType GetBSTValue(pBSNode pBSN)
{
	return pBSN->data;
}

BSTElemType GetBSTMin(BSTree BST)
{
	pBSNode		pBSN;

	if ((pBSN = FindMin(BST)) == NULL)
		err_msg("Can't Find Min in BSTree");
	return GetBSTValue(pBSN);
}
BSTElemType GetBSTMax(BSTree BST)
{
	pBSNode		pBSN;

	if ((pBSN = FindMax(BST)) == NULL)
		err_msg("Can't Find Min in BSTree");

	return GetBSTValue(pBSN);

}
void DeleteBSTNode(BSTree *BST, BSTElemType x)
{
	pBSNode		pBSNbck = *BST;
	pBSNode		pBSN;
	pBSNode		tmp;

	if (*BST == NULL)
		err_msg("DeleteBSTNode error");

	if (x < (*BST)->data)
		pBSN = pBSNbck->left;
	if (x > (*BST)->data)
		pBSN = pBSNbck->right;

	if ((*BST)->data != x)
	{
		while (pBSN != NULL && pBSN->data != x)
		{
			pBSNbck = pBSN;
			if (x < pBSN->data)
			{
				pBSN = pBSN->left;
				continue;
			}
			if (x > pBSN->data)
			{
				pBSN = pBSN->right;
				continue;
			}
		}
	}
	else 
	{
		free(*BST);
		*BST = NULL;
		return ;
	}

	if (pBSN == NULL)
		err_msg("%d is not in this BSTree");

	if (pBSN->left && pBSN->right)
	{
		tmp = FindMin(pBSN->right);	
		pBSN->data = GetBSTValue(tmp);
		//DeleteBSTNode(&(pBSN->right), GetBSTValue(tmp));
		DeleteBSTNode(&(pBSN->right), tmp->data);
	}
	else
	{
		if (pBSN == pBSNbck->left )
		{
			if (pBSN->left == NULL)
				pBSNbck->left = pBSN->right;
			else if (pBSN->right == NULL)
				pBSNbck->left = pBSN->left;
			free(pBSN);
		}
		else if (pBSN == pBSNbck->right)
		{
			if (pBSN->left == NULL)
				pBSNbck->right = pBSN->right;
			else if (pBSN->right == NULL)
				pBSNbck->right = pBSN->left;
			free(pBSN);
		}
		else 
			err_msg("pBSN != pBSNbck->right");

	}
}
void DeleteBSTMin(BSTree *BST)
{
//	DeleteBSTNode(BST, GetBSTValue(FindMin(*BST)));
	pBSNode		pBSN;
	pBSNode		pBSNbck;

	if (*BST == NULL)
		err_msg("DeleteBSTMin in a empty BSTree");

	pBSNbck = *BST;
	if (pBSNbck->left)
	{
		pBSN = pBSNbck->left;

		while (pBSN->left != NULL)
		{
			pBSNbck = pBSN;
			pBSN = pBSN->left;
		}
		if (pBSN->right)
			pBSNbck->left = pBSN->right;
		free(pBSN);
		pBSNbck->left = NULL;
	}
	else 
	{
		if (pBSNbck->right)
			pBSN = pBSNbck->right;
		free(*BST);
		*BST = pBSN;
		
	}
}
void DeleteBSTMax(BSTree *BST)
{
//	DeleteBSTNode(BST, GetBSTValue(FindMax(*BST)));
	pBSNode		pBSN;
	pBSNode		pBSNbck;

	if (*BST == NULL)
		err_msg("DeleteBSTMax in a empty BSTree");

	pBSNbck = *BST;

	if (pBSNbck->right)
	{
		pBSN = pBSNbck->right;
		while (pBSN->right != NULL)
		{
			pBSNbck = pBSN;
			pBSN = pBSN->right;
		}
		if (pBSN->left)
			pBSNbck->right = pBSN->left;
		free(pBSN);
		pBSNbck->right = NULL;
	}
	else 
	{
		if (pBSNbck->left)
			pBSN = pBSNbck->left;
		free(*BST);
		*BST = pBSN;
	}
}
