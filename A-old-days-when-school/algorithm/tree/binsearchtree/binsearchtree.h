#ifndef  BINSEARCHTREE_H
#define  BINSEARCHTREE_H

#include    "bintree.h"

typedef BinTreeNode BinSTreeNode;
typedef BinTree BinSTree;
typedef int	Elmt;

void binstree_insert(BinSTree *bstree, Elmt x);
void binstree_remove(BinSTree *bstree, Elmt x);

BinSTreeNode** binstree_findxparent_position(BinSTree *bstree, Elmt x);
BinSTreeNode* binstree_findx_position(BinSTree *bstree, Elmt x);
Elmt binstree_findMax(BinSTree *bstree);
Elmt binstree_findMin(BinSTree *bstree);
Elmt binstree_retrieve(BinSTreeNode *position);

#define		binstree_init bintree_init
#define		binstree_destroy bintree_destroy 

#define		binstree_preorder_treverse bintree_preorder_treverse
#define		binstree_inorder_treverse bintree_inorder_treverse
#define		binstree_postorder_treverse bintree_postorder_treverse

#define		binstree_nonrecursion_preorder_treverse \
	bintree_nonrecursion_preorder_treverse
#define		binstree_nonrecursion_inorder_treverse \
	bintree_nonrecursion_inorder_treverse
#define		binstree_nonrecursion_postorder_treverse \
	bintree_nonrecursion_postorder_treverse

#define		binstree_levelorder_treverse \
	bintree_levelorder_treverse

#define		binstree_depth bintree_depth

#define		binstree_is_empty bintree_is_empty
#define		binstree_is_eob bintree_is_eob
#define		binstree_is_leaf bintree_is_leaf

#define		binstree_size bintree_size
#define		binstree_root bintree_root
#define		binstree_data bintree_data
#define		binstree_left bintree_left
#define		binstree_right bintree_right



#endif  /*BINSEARCHTREE_H*/
