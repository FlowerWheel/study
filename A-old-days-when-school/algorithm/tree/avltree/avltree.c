#include	"avltree.h"
#include	<assert.h>


static int Height(AvlTreeNode *node)
{
	if (node == NULL)
		return -1;
	else 
		return node->height;
}

static int Max(int a, int b)
{
	return a > b ? a : b;
}

static int MaxHeight(AvlTreeNode *left, AvlTreeNode *right)
{
	return Max(Height(left), Height(right)) + 1;
}

static AvlTreeNode * SingleRotateWithLeft(AvlTreeNode *k2)
{//LL
	AvlTreeNode * k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
	return k1;
}

static AvlTreeNode * SingleRotateWithRight(AvlTreeNode *k2)
{//RR	
	AvlTreeNode * k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
	return k1;
}

static AvlTreeNode * DoubleRotateWithLeft(AvlTreeNode *k3)
{//LR
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}

static AvlTreeNode * DoubleRotateWithRight(AvlTreeNode *k3)
{//RL
	k3->right = SingleRotateWithLeft(k3->right);
	return SingleRotateWithRight(k3);
}

static AvlTreeNode* avl_rotate_for_insert(AvlTreeNode **node)
{//for insert
	if (Height((*node)->left) - Height((*node)->right) == 2)
	{//left
		if (Height((*node)->left->left) >= Height((*node)->left->right))
			*node = SingleRotateWithLeft(*node);
		else
			*node = DoubleRotateWithLeft(*node);
	}
	if (Height((*node)->right) - Height((*node)->left) == 2)
	{//right
		if (Height((*node)->left->left) >= Height((*node)->left->right))
			*node = SingleRotateWithRight(*node);
		else
			*node = DoubleRotateWithRight(*node);
	}
	return *node;
}

static AvlTreeNode* avl_rotate_for_remove(AvlTreeNode **node)
{//for remove 
	if (Height((*node)->left) - Height((*node)->right) == 2)
	{
		if ((*node)->left != NULL && (*node)->right != NULL)
			*node = SingleRotateWithLeft(*node);
		else if ((*node)->left != NULL)
		{
			if ((*node)->left->left != NULL && (*node)->left->right != NULL)
				*node = SingleRotateWithLeft(*node);
			else if ((*node)->left->left != NULL)
				*node = SingleRotateWithLeft(*node);
			else if ((*node)->left->right != NULL)
				*node = DoubleRotateWithRight(*node);
			else
			{}
		}
		/* else if ((*node)->right != NULL) { // } else { // } */
	}

	if (Height((*node)->right) - Height((*node)->left) == 2)
	{
		if ((*node)->left != NULL && (*node)->right != NULL)
			*node = SingleRotateWithRight(*node);
		else if ((*node)->right != NULL)
		{
			if ((*node)->right->left != NULL && (*node)->right->right != NULL)
				*node = SingleRotateWithRight(*node);
			else if ((*node)->right->left != NULL)
				*node = DoubleRotateWithRight(*node);
			else if ((*node)->right->right != NULL)
				*node = SingleRotateWithRight(*node);
			else
			{}
		}
		/* else if ((*node)->right != NULL) {} else {} */
	}

	return *node;
}

static AvlTreeNode * avl_insert(AvlTree *avltree, AvlTreeNode **node, Elmt x)
{
	if (*node == NULL)
	{
		if ((*node = malloc(sizeof(AvlTreeNode))) == NULL)
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
				++avltree->size;
			}
		}
	}
	else if (x < *(int*)((*node)->data))
	{
		/*(*node)->left =*/ 
		avl_insert(avltree, &(*node)->left, x);
		//avl_rotate(node);
		if (Height((*node)->left) - Height((*node)->right) == 2)
		{
			if (x < *(int*)((*node)->right->data))
				*node = SingleRotateWithLeft(*node);
			else
				*node = DoubleRotateWithLeft(*node);
		}
	}
	else if (x > *(int*)((*node)->data))
	{
		/*(*node)->right =*/ 
		avl_insert(avltree, &(*node)->right, x);
		//avl_rotate(node);
		if (Height((*node)->right) - Height((*node)->left) == 2)
		{
			if (x > *(int*)((*node)->right->data))
				*node = SingleRotateWithRight(*node);
			else
				*node = DoubleRotateWithRight(*node);
		}
	}
	else 
	{ /*nothing to do*/ }

	(*node)->height = MaxHeight((*node)->left, (*node)->right);
	return *node;
}

void avltree_insert(AvlTree *avltree, Elmt x)
{
	avl_insert(avltree, &avltree->root, x);
}

static void avl_delete_min(AvlTree *avltree, AvlTreeNode **node, Elmt *e)
{
	/* assert(node != NULL); */
	if ((*node)->left == NULL)
	{
		*e = *(int*)(*node)->data;		
		if ((*node)->right)
		{
			*(int*)((*node)->data) = *(int*)((*node)->right->data);
			*node = (*node)->right;
		}
		free((*node)->data);
		free(*node);
		*node = NULL;
		--(avltree->size);
	}
	else
	{
		avl_delete_min(avltree, &(*node)->left, e);
//		avl_rotate_for_remove(node);
//		(*node)->height = MaxHeight((*node)->left, (*node)->right);
	}

}

Elmt avltree_delete_min(AvlTree *avltree)
{
	Elmt	e;
	avl_delete_min(avltree, &(avltree->root), &e);
	return	e;
}

static AvlTreeNode * avl_remove(AvlTree *avltree, AvlTreeNode **node, Elmt x)
{
	if (*node != NULL)	
		return NULL;

	if (x == *(int*)(*node)->data)
	{
		if ((*node)->left == NULL && (*node)->right == NULL)
		{
			free((*node)->data);
			free((*node));
			*node = NULL;
		}
		else if ((*node)->left == NULL)/*(*node)->right != NULL*/
		{
			free((*node)->data);
			(*node)->data = (*node)->right->data;
			free((*node)->right);
			(*node)->right = NULL;
		}
		else if ((*node)->right == NULL)/*(*node)->left != NULL*/
		{
			free((*node)->data);
			(*node)->data = (*node)->left->data;
			free((*node)->left);
			(*node)->left = NULL;
		}
		else /*((*node)->left != NULL & (*node)->right != NULL)*/
		{
			Elmt	e;
			avl_delete_min(avltree, &(*node)->right, &e);	
			*(int*)(*node)->data = e;
			++(avltree->size);
		}
		--(avltree->size);
	}
	else if (x < *(int*)(*node)->data) 
	{
		(*node)->left = avl_remove(avltree, &(*node)->left, x);
		avl_rotate_for_remove(node);
		(*node)->height = MaxHeight((*node)->left, (*node)->right);
	}
	else /*if (x > *(int*)(*node)->data)*/
	{
		(*node)->right = avl_remove(avltree, &(*node)->right, x);
		avl_rotate_for_remove(node);
		(*node)->height = MaxHeight((*node)->left, (*node)->right);
	}
	return *node;
}

static AvlTreeNode * avl_delete(AvlTree *avltree, AvlTreeNode **node, Elmt x)
{
	AvlTreeNode *pos;
	if (*node != NULL)	
		return NULL;

	if (x == *(int*)(*node)->data)
	{
		if (!(*node)->left)
		{
			pos = (*node);
			*node = (*node)->right;
			free(pos);
		}
		else if(!(*node)->right)
		{
			pos = (*node);
			*node = (*node)->left;
			free(pos);
		}
		else
		{
			Elmt	e;
			avl_delete_min(avltree, &(*node)->right, &e);
			*(int*)(*node)->data = e;
			if (Height((*node)->left) - Height((*node)->right) == 2)
			{
				if (Height((*node)->left->right - Height((*node)->left->left)) == 1)
					(*node) = DoubleRotateWithLeft(*node);
				else 
					(*node) = SingleRotateWithLeft(*node);
			}
			++(avltree->size);
		}
		--(avltree->size);
	}
	else if (x < *(int*)(*node)->data) 
	{
		(*node)->left = avl_remove(avltree, &(*node)->left, x);
		if (Height((*node)->right) - Height((*node)->left) == 2)
		{
			if ((*node)->left == NULL)
			{
				if ((*node)->right->right == NULL)
					*node = DoubleRotateWithRight(*node);
				else 
					*node = SingleRotateWithRight(*node);
			}
			else if (x < *(int*)(*node)->left->data)
				*node = DoubleRotateWithLeft(*node);
			else 
				*node = SingleRotateWithLeft(*node);

		}
	}
	else /*if (x > *(int*)(*node)->data)*/
	{
		(*node)->right = avl_remove(avltree, &(*node)->right, x);
		if (Height((*node)->left) - Height((*node)->right) == 2)
		{
			if ((*node)->right == NULL)
			{
				if ((*node)->left->left == NULL)
					*node = DoubleRotateWithRight(*node);
				else 
					*node = SingleRotateWithRight(*node);
			}
			else if (x < *(int*)(*node)->right->data)
				*node = SingleRotateWithRight(*node);
			else 
				*node = DoubleRotateWithRight(*node);

		}
	}
	if (*node) (*node)->height = MaxHeight((*node)->left, (*node)->right);
	return *node;
}

void avltree_remove(AvlTree *avltree, Elmt x)
{
	//avl_remove(avltree, &avltree->root, x);
	avl_delete(avltree, &avltree->root, x);
}
