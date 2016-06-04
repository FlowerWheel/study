#ifndef  AVLTREE_H
#define  AVLTREE_H

#include    "bintree.h"
#include    "binsearchtree.h"

typedef BinTreeNode AvlTreeNode;
typedef BinTree AvlTree;
typedef int	Elmt;

void avltree_insert(AvlTree *avltree, Elmt x);
void avltree_remove(AvlTree *avltree, Elmt x);

Elmt avltree_delete_min(AvlTree *avltree);
Elmt avltree_delete_max(AvlTree *avltree);

#define		avltree_findxparent_position binstree_findxparent_position
#define		avltree_findx_position binstree_findx_position
#define		avltree_findMax binstree_findMax
#define		avltree_findMin binstree_findMin
#define		avltree_retrieve binstree_retrieve

#define		avltree_init bintree_init
#define		avltree_destroy bintree_destroy 

#define		avltree_preorder_treverse bintree_preorder_treverse
#define		avltree_inorder_treverse bintree_inorder_treverse
#define		avltree_postorder_treverse bintree_postorder_treverse

#define		avltree_nonrecursion_preorder_treverse \
	bintree_nonrecursion_preorder_treverse
#define		avltree_nonrecursion_inorder_treverse \
	bintree_nonrecursion_inorder_treverse
#define		avltree_nonrecursion_postorder_treverse \
	bintree_nonrecursion_postorder_treverse

#define		avltree_levelorder_treverse \
	bintree_levelorder_treverse

#define		avltree_depth bintree_depth

#define		avltree_is_empty bintree_is_empty
#define		avltree_is_eob bintree_is_eob
#define		avltree_is_leaf bintree_is_leaf

#define		avltree_size bintree_size
#define		avltree_root bintree_root
#define		avltree_data bintree_data
#define		avltree_left bintree_left
#define		avltree_right bintree_right

#endif  /*AVLTREE_H*/
