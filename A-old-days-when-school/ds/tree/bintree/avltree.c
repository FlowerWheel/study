#include "avltree.h"
#include "lueap.h"


void InitAVL(AvlTree *Avl)
{
	*Avl = NULL;
}
void DestoryAVL(AvlTree *Avl)
{
	if (*Avl != NULL)
	{
		DestoryAVL(&(*Avl)->left);
		DestoryAVL(&(*Avl)->right);
		free(*Avl);
	}
	*Avl = NULL;
}
int	 IsEmptyAVL(AvlTree Avl)
{
	return (Avl == NULL);
}
int	 DepAVL(const AvlTree Avl)
{
	int leftDep, rightDep;
	leftDep = rightDep = -1;
	if (Avl != NULL)
	{
		leftDep = DepAVL(Avl->left);
		rightDep = DepAVL(Avl->right);
	}
	return ((leftDep > rightDep) ? ++leftDep : ++ rightDep);
}
static int Height(pAvlNode p)
{
	if (p == NULL)
		return -1;
	else 
		return p->height;
}
static int HeightUpdate(AvlTree Avl)
{
	if (Avl == NULL)
		return -1;
	Avl->height = Max(HeightUpdate(Avl->left), HeightUpdate(Avl->right)) + 1;
	return Avl->height;
}

pAvlNode Find(AvlTree Avl, AvlElemType x)
{
	if (Avl == NULL)
		return NULL;
	if (x < Avl->data)
		return Find(Avl->left, x);
	else if (x > Avl->data)
		return Find(Avl->right, x);
	else 
		return Avl;
}
pAvlNode FindMin(AvlTree Avl)
{
	pAvlNode	pAvl = Avl;
	if (Avl == NULL)
		return NULL;
	while (pAvl->left)
		pAvl = pAvl->left;
	return pAvl;

}
pAvlNode FindMax(AvlTree Avl)
{
	pAvlNode	pAvl = Avl;
	if (Avl == NULL)
		return NULL;
	while (pAvl->right)
		pAvl = pAvl->right;
	return pAvl;
}
static pAvlNode SingleRotateWithLeft(pAvlNode k2)
{
	pAvlNode	k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), Height(k1->right)) + 1;

	return k1;
}
static pAvlNode SingleRotateWithRight(pAvlNode k2)
{
	pAvlNode	k1;

	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = Max(Height(k1->left), Height(k1->right)) + 1;

	return k1;
}
static pAvlNode DoubleRotateWithLeft(pAvlNode k3)
{
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}
static pAvlNode DoubleRotateWithRight(pAvlNode k3)
{
	k3->left = SingleRotateWithLeft(k3->left);
	return SingleRotateWithRight(k3);
}
AvlTree InsertAVL(AvlTree *Avl, AvlElemType x)
{
	if (*Avl == NULL)
	{
		*Avl = malloc(sizeof(struct AvlNode));
		if (*Avl == NULL)
			err_sys("malloc error");
		else 
		{
			(*Avl)->left = NULL;
			(*Avl)->right = NULL;
			(*Avl)->data = x;
			(*Avl)->height = 0;
		}
	}
	else if (x < (*Avl)->data)
	{
		(*Avl)->left = InsertAVL(&(*Avl)->left, x);
		if (Height((*Avl)->left) - Height((*Avl)->right) == 2)
		{
			if (x < (*Avl)->left->data)
				*Avl = SingleRotateWithLeft(*Avl);
			else
				*Avl = DoubleRotateWithLeft(*Avl);
		}
	}
	else if (x > (*Avl)->data)
	{
		(*Avl)->right = InsertAVL(&(*Avl)->right, x);
		if (Height((*Avl)->right) - Height((*Avl)->left) == 2)
		{
			if (x > (*Avl)->right->data)
				*Avl = SingleRotateWithRight(*Avl);
			else
				*Avl = DoubleRotateWithRight(*Avl);
		}
	}
	else 
		err_msg("%d already exist");
	(*Avl)->height = Max(Height((*Avl)->left), Height((*Avl)->right)) + 1;
	return (*Avl);
}
void DeleteAVLNode(AvlTree *avl, AvlElemType x)
{
	pAvlNode	*ppavl = avl;
	pAvlNode	*ppavl_save;
	pAvlNode	ptmp;
	pAvlNode	tmp;

	if (*avl == NULL)	
		err_msg("DeleteAVLNode error");

	if (x < (*ppavl)->data)
		DeleteAVLNode(&(*ppavl)->left, x);
	else if (x > (*ppavl)->data)
		DeleteAVLNode(&(*ppavl)->right, x);
	else /*x == (*ppavl)->data*/
	{
		ppavl_save = ppavl;

		if (Height(*ppavl) > 0)
		{
			if (Height((*ppavl)->left) > Height((*ppavl)->right))
			{
				ptmp = *ppavl;
				tmp = (*ppavl)->left;	
				while (tmp->right != NULL)
				{
					ptmp = tmp;
					tmp = tmp->right;
				}
				(*ppavl_save)->data = tmp->data;
				free(ptmp);
				ptmp = NULL;
				HeightUpdate((*ppavl)->left);
			}
			else /*if (Height((*ppavl)->left) <= Height((*ppavl)->right))*/
			{
				ptmp = *ppavl;
				tmp = (*ppavl)->right;	
				while (tmp->left != NULL)
				{
					ptmp = tmp;
					tmp = tmp->left;
				}
				(*ppavl_save)->data = tmp->data;
				free(ptmp);
				ptmp = NULL;
				HeightUpdate((*ppavl)->right);
			}
			if (Height((*avl)->left) - Height(((*avl)->right)) == 2)
				*avl = SingleRotateWithLeft(*avl);
			else if (Height((*avl)->right) - Height(((*avl)->left)) == 2)
				*avl = SingleRotateWithRight(*avl);
			else 
				/**/;
		}
		else
		{
			free(*ppavl);
			*ppavl = NULL;
		}	
	}

	(*avl)->height = Max(Height((*avl)->left), Height((*avl)->right)) + 1;
//	(*avl)->height = HeightUpdate(*avl);
}
void CreateAVL(AvlTree *Avl)
{
	AvlElemType		avle;
	while (scanf("%d", &avle) != EOF)
		InsertAVL(Avl, avle);
}
AvlElemType RetrieveAVL(pAvlNode p)
{
	AvlElemType e = 1;
	return e;
}

void PreTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height))
{
	if (Avl != NULL)
	{
		visit(Avl->data, Avl->height);
		PreTraverseAVL(Avl->left, visit);
		PreTraverseAVL(Avl->right, visit);
	}
}
void InTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height))
{
	if (Avl != NULL)
	{
		InTraverseAVL(Avl->left, visit);
		visit(Avl->data, Avl->height);
		InTraverseAVL(Avl->right, visit);
	}
}
void PostTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height))
{
	if (Avl != NULL)
	{
		PostTraverseAVL(Avl->left, visit);
		PostTraverseAVL(Avl->right, visit);
		visit(Avl->data, Avl->height);
	}
}

