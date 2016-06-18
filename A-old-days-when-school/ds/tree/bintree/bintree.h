#ifndef _BINTREE_H_
#define _BINTREE_H_

#include "type.h"
#include "lueap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/errno.h>

#include "stack.h"
#include "queue.h"

//#include <vector>
//#include <queue>

struct BinTreeNode{
	BTElemType			data;
	struct BinTreeNode	*left;
	struct BinTreeNode	*right;
};

typedef struct BinTreeNode *BinTree, BTNode, *pBTNode;

void InitBinTree(BinTree *BT);
void MakeEmptyBinTree(BinTree *BT);
void DestoryBinTree(BinTree *BT);
int	 IsEmptyBinTree(const BinTree BT);
int	 DepBinTree(const BinTree BT);
void PreCreateBinTree(BinTree *BT);
void PreTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void InTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void PostTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void nonRecursivePreTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void nonRecursiveInTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void nonRecursivePostTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));
void LevelTraverseBinTree(const BinTree BT, void (*visit)(BTElemType e));

#endif /*_BINTREE_H_*/
