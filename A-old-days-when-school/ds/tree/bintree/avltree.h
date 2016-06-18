#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "type.h"
#include "stack.h"
#include "queue.h"
#include "lueap.h"

#define AvlElemType		int

struct AvlNode;
typedef struct AvlNode AvlNode;
typedef struct AvlNode *pAvlNode;
typedef struct AvlNode *AvlTree;

struct AvlNode {
	int				height;
	AvlElemType		data;
	struct AvlNode *left;
	struct AvlNode *right;
};

void InitAVL(AvlTree *Avl);
void CreateAVL(AvlTree *Avl);
void DestoryAVL(AvlTree *Avl);
int	 IsEmptyAVL(const AvlTree Avl);
int	 DepAVL(const AvlTree Avl);

void DeleteAVLNode(AvlTree *avl, AvlElemType x);
pAvlNode Find(AvlTree Avl, AvlElemType x);
pAvlNode FindMin(AvlTree Avl);
pAvlNode FindMax(AvlTree Avl);
AvlElemType GetAVLvalue(pAvlNode p);

AvlTree InsertAVL(AvlTree *AvlTree, AvlElemType x);
AvlElemType RetrieveAVL(pAvlNode p);

void PreTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height));
void InTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height));
void PostTraverseAVL(const AvlTree Avl, void (*visit)(AvlElemType e, int height));

#endif /*_AVLTREE_H_*/
