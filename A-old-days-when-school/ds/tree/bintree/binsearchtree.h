#ifndef _BSTREE_H_
#define _BSTREE_H_

#include "lueap.h"
#include "type.h"
#include "bintree.h"

#ifdef BTElemType
#undef BTElemType
#endif /*BTElemType*/

#define BTElemType int
#define BSTElemType BTElemType

typedef	struct BinTreeNode BSBinTreeNode;

typedef BSBinTreeNode *BSTree, *pBSNode, BSNode;

#define InitBSTree(BST) InitBinTree(BST)
#define MakeEmptyBSTree(BST) MakeEmptyBinTree(BST)
#define DestoryBSTree(BST) DestoryBinTree(BST)
#define IsEmptyBSTree(BST) IsEmptyBinTree(BST)
#define DepBSTree(BST) DepBinTree(BST)

void CreatBSTree(BSTree *BST);
void InsertBSTree(BSTree *BST, BSTElemType x);

pBSNode Find(BSTree BST, BSTElemType x);
pBSNode FindMin(BSTree BST);
pBSNode FindMax(BSTree BST);

BSTElemType GetBSTValue(pBSNode pBSN);
BSTElemType GetBSTMin(BSTree BST);
BSTElemType GetBSTMax(BSTree BST);

void DeleteBSTNode(BSTree *BST, BSTElemType x);
void DeleteBSTMin(BSTree *BST);
void DeleteBSTMax(BSTree *BST);

#endif /*_BSTREE_H_*/
