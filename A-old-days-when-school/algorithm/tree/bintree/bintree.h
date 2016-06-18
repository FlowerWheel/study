#ifndef  BINTREE_H
#define  BINTREE_H

#include    <stdlib.h>

typedef struct _BinTreeNode{
	void					*data;
	int						height; //used for avltree
	struct _BinTreeNode		*left;
	struct _BinTreeNode		*right;
}BinTreeNode;

typedef struct _BinTree{
	int		size;
	int		(*compare)(const void *key1, const void *key2);
	void	(*destroy)(void *data);
	BinTreeNode *root;
}BinTree;

/*Public Interface*/
void bintree_init(BinTree *tree, void (*destroy)(void *data));
void bintree_destroy(BinTree *tree);

int  bintree_insert_left(BinTree *tree, BinTreeNode *node, const void *data);
int  bintree_insert_right(BinTree *tree, BinTreeNode *node, const void *data);

void bintree_remove_left(BinTree *tree, BinTreeNode *node);
void bintree_remove_right(BinTree *tree, BinTreeNode *node);

int  bintree_merge(BinTree *merge, BinTree *left, BinTree *right, const void *data);

void bintree_preorder_create(BinTree *tree, void *(*get_data)(void));
void bintree_preorder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_inorder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_postorder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_nonrecursion_preorder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_nonrecursion_inorder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_nonrecursion_postorder_treverse(BinTree *tree, void (*op)(void *data));

void bintree_LevelOrder_treverse(BinTree *tree, void (*op)(void *data));
void bintree_levelorder_treverse(BinTree *tree, void (*op)(void *data));

int  bintree_depth(BinTree tree);

#define bintree_is_empty(tree) ( (tree).size == 0 ? 1 : 0 )
#define bintree_is_eob(node) ( (node) == NULL )
#define bintree_is_leaf(node) ( (node)->left == NULL && (node)->right == NULL )

#define bintree_size(tree) ( (tree).size )
#define bintree_root(tree) ( (tree).root )
#define bintree_data(node) ( (node)->data )
#define bintree_left(node) ( (node)->left )
#define bintree_right(node) ( (node)->right )

#endif  /*BINTREE_H*/
