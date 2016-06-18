#ifndef  CSTREE_H
#define  CSTREE_H

typedef struct _CSTreeNode{
	void				*data;
	struct _CSTreeNode	*NextSibling;
	struct _CSTreeNode	*FirstChild;
}CSTreeNode;

typedef struct _CSTree{
	int			size;
	CSTreeNode	*root;
	void (*compare)(const void *key1, const void *key2);
	void (*destroy)(void *data);
}CSTree;

void cstree_init(CSTree *cst, void (*destroy)(void *data));
void cstree_destroy(CSTree *cst);

void cstree_create(CSTree *cst, void (*get_data)(void *data));



#endif  /*CSTREE_H*/
