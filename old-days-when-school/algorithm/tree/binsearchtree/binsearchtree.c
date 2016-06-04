#include    "binsearchtree.h"

static BinSTreeNode* bst_insert(BinSTree *bstree, BinSTreeNode **node, Elmt x)
{
	if (*node == NULL)
	{
		if ((*node = malloc(sizeof(BinSTreeNode))) == NULL)
			return NULL;
		else
		{
			if (((*node)->data = malloc(sizeof(int))) == NULL)
			{
				free(*node);
				return NULL;
			}
			else
			{
				*(int*)((*node)->data) = x;
				(*node)->left = NULL;
				(*node)->right = NULL;
				++bstree->size;
			}
		}
	}
	else if (x > *(int*)((*node)->data))
		(*node)->right = bst_insert(bstree, &(*node)->right, x);
	else if (x < *(int*)((*node)->data))
		(*node)->left = bst_insert(bstree, &(*node)->left, x);
	else 
		/*nothing to do*/;
	return *node;
}

void binstree_insert(BinSTree *bstree, Elmt x)
{
	if (bstree == NULL)
		return ;
	/*bstree->root =*/ 
	bst_insert(bstree, &bstree->root, x);
}

static BinSTreeNode* bst_remove(BinSTree *bstree, BinSTreeNode **node, Elmt x)
{
	BinSTreeNode *tmp_node;
	if (*node == NULL)
		return NULL;
	else if (x < *(int*)((*node)->data))
		(*node)->left = bst_remove(bstree, &(*node)->left, x);
	else if (x > *(int*)((*node)->data))
		(*node)->right = bst_remove(bstree, &(*node)->right, x);
	else
	{
		tmp_node = *node;
		if ((*node)->left == NULL)
			*node = (*node)->right;
		else if ((*node)->right == NULL)
			*node = (*node)->left;
		free(tmp_node);
		--bstree->size;
	}
	return *node;
}

void binstree_remove(BinSTree *bstree, Elmt x)
{
	if (bstree == NULL)
		return ;
	bstree->root = bst_remove(bstree, &bstree->root, x);
}

static BinSTreeNode** bst_findxparent_position(BinSTreeNode **node, Elmt x)
{
	if (*node != NULL)
	{
		if (x == *(int*)(*node)->data)
			return node;
		else if (x < *(int*)(*node)->data)
			return bst_findxparent_position(&(*node)->left, x);
		else /*if (x > *(int*)(*node)->data)*/
			return bst_findxparent_position(&(*node)->right, x);
	}
	return NULL;
}

BinSTreeNode** bstree_findxparent_position(BinSTree *bstree, Elmt x)
{
	if (bstree == NULL)
		return NULL;
	else 
		return bst_findxparent_position(&bstree->root, x);
}

BinSTreeNode* binstree_findx_position(BinSTree *bstree, Elmt x)
{
	BinSTreeNode *pbstnode;
	BinSTreeNode **pbstnodep;

	if (bstree == NULL)	
		return NULL;
	else 
	{
		pbstnodep = bst_findxparent_position(&bstree->root, x);
		if (pbstnodep != NULL)
			return pbstnode = *pbstnodep;
		else 
			return NULL;
	}
}

Elmt binstree_findMax(BinSTree *bstree)
{
	BinSTreeNode *node;
	if (bstree != NULL)
	{
		node = bstree->root;
		while (node->right != NULL)
			node = node->right;
	}
	return binstree_retrieve(node);
}

Elmt binstree_findMin(BinSTree *bstree)
{
	BinSTreeNode *node;
	if (bstree != NULL)
	{
		node = bstree->root;
		while (node->left != NULL)
			node = node->left;
	}
	return binstree_retrieve(node);
}

Elmt binstree_retrieve(BinSTreeNode *position)
{
	if (position == NULL)
		return -1;
	return *(int*)(position->data);
}
