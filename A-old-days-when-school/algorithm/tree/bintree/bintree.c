#include "bintree.h"
#include "stack.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>

void bintree_init(BinTree *tree, void (*destroy)(void *data))
{
	tree->size = 0;
	tree->root = NULL;
	tree->destroy = destroy;
	return ;
}

void bintree_destroy(BinTree *tree/*, void (*destroy)(void *data)*/)
{
	bintree_remove_left(tree, NULL);
	memset(tree, 0, sizeof(BinTreeNode));
	return ;
}

int  bintree_insert_left(BinTree *tree, BinTreeNode *node, const void *data)
{
	BinTreeNode *new_node, **position;
	if (node == NULL)
	{
		if (bintree_size(*tree) > 0)
			return -1;
		position = &tree->root;
	}
	else
	{
		if (bintree_left(node) != NULL)
			return -1;
		position = &node->left;
	}
	if ((new_node = malloc(sizeof(BinTreeNode))) == NULL)
		return -1;
	new_node->data = (void*)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;
	++(tree->size);
	return 0;
}
	
int  bintree_insert_right(BinTree *tree, BinTreeNode *node, const void *data)
{
	BinTreeNode *new_node, **position;
	if (node == NULL)
	{
		if (bintree_size(*tree) > 0)
			return -1;
		position = &tree->root;
	}
	else
	{
		if (bintree_right(node) != NULL)
			return -1;
		position = &node->right;
	}
	if ((new_node = malloc(sizeof(BinTreeNode))) == NULL)
		return -1;
	new_node->data = (void*)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;
	++(tree->size);
	return 0;

}
void bintree_remove_left(BinTree *tree, BinTreeNode *node)
{
	BinTreeNode		**position;
	if (bintree_size(*tree) == 0)
		return ;

	if (node == NULL)
		position = &tree->root;
	else 
		position = &node->left;

	if (*position != NULL)
	{
		bintree_remove_left(tree, *position);
		bintree_remove_right(tree, *position);
		if (tree->destroy != NULL)
			tree->destroy((*position)->data);
		free(*position);
		*position = NULL;
		--(tree->size);
	}
}
void bintree_remove_right(BinTree *tree, BinTreeNode *node)
{
	BinTreeNode		**position;
	if (bintree_size(*tree) == 0)
		return ;

	if (node == NULL)
		position = &tree->root;
	else 
		position = &node->right;

	if (*position != NULL)
	{
		bintree_remove_left(tree, *position);
		bintree_remove_right(tree, *position);
		if (tree->destroy != NULL)
			tree->destroy((*position)->data);
		free(*position);
		*position = NULL;
		--(tree->size);
	}
}

int  bintree_merge(BinTree *merge, BinTree *left, BinTree *right, const void *data)
{
	bintree_init(merge, left->destroy);
	
	if (bintree_insert_left(merge, NULL, data) != 0)
	{
		bintree_destroy(merge);
		return -1;
	}
	bintree_root(*merge)->left = bintree_root(*left);
	bintree_root(*merge)->right = bintree_root(*right);
	merge->size = merge->size + bintree_size(*left) + bintree_size(*right);
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;
	return 0;
}

static void pre_create(BinTreeNode **node, void *(*get_data)(void))
{
	BinTreeNode		*new_node;
	void			*ptr_data;

	if ((ptr_data = get_data()) != NULL)
	{
		if ((new_node = malloc(sizeof(BinTreeNode))) == NULL)	
				return ;
		new_node->data = ptr_data;
		*node = new_node;
		pre_create(&(*node)->left, get_data);
		pre_create(&(*node)->right, get_data);
	}
	else 
		*node = NULL;

}

void bintree_preorder_create(BinTree *tree, void *(*get_data)(void))
{
	pre_create(&tree->root, get_data);
}

static void pre_treverse(BinTreeNode *node, void (*op)(void *data))
{
	if (node != NULL)
	{
		op(node->data);
		pre_treverse(node->left, op);
		pre_treverse(node->right, op);
	}
}

void bintree_preorder_treverse(BinTree *tree, void (*op)(void *data))
{
	pre_treverse(tree->root, op);	
}

static void in_treverse(BinTreeNode *node, void (*op)(void *data))
{
	if (node != NULL)
	{
		in_treverse(node->left, op);
		op(node->data);
		in_treverse(node->right, op);
	}
}

void bintree_inorder_treverse(BinTree *tree, void (*op)(void *data))
{
	in_treverse(tree->root, op);	
}

static void post_treverse(BinTreeNode *node, void (*op)(void *data))
{
	if (node != NULL)
	{
		post_treverse(node->left, op);
		post_treverse(node->right, op);
		op(node->data);
	}
}

void bintree_postorder_treverse(BinTree *tree, void (*op)(void *data))
{
	post_treverse(tree->root, op);	
}

void bintree_nonrecursion_preorder_treverse(BinTree *tree, void (*op)(void *data))
{
	BinTreeNode *root = tree->root;
	BinTreeNode *top;
	Stack	node_stack;

	stack_init(&node_stack, NULL);
	if (root)
		stack_push(&node_stack, root);
	while(!stack_is_empty(node_stack))
	{
		while( top = stack_top(node_stack), top )
		{
			op(top->data);
			stack_push(&node_stack, top->left);
		}
		stack_pop(&node_stack);
		if (!stack_is_empty(node_stack))
		{
			top = stack_top(node_stack);
			stack_pop(&node_stack);
			stack_push(&node_stack, top->right);
		}
	}
	stack_destroy(&node_stack);
}

void bintree_nonrecursion_inorder_treverse(BinTree *tree, void (*op)(void *data))
{
	BinTreeNode *root = tree->root;
	BinTreeNode *top;
	Stack	node_stack;

	stack_init(&node_stack, NULL);
	if (root)
		stack_push(&node_stack, root);
	while(!stack_is_empty(node_stack))
	{
		while( top = stack_top(node_stack), top )
		{
			stack_push(&node_stack, top->left);
		}
		stack_pop(&node_stack);
		if (!stack_is_empty(node_stack))
		{
			top = stack_top(node_stack);
			op(top->data);
			stack_pop(&node_stack);
			stack_push(&node_stack, top->right);
		}
	}
	stack_destroy(&node_stack);

}

void bintree_nonrecursion_postorder_treverse(BinTree *tree, void (*op)(void *data))
{
	BinTreeNode	*root = tree->root;
	BinTreeNode *top, *pre;
	Stack node_stack;

	stack_init(&node_stack, NULL);
	if (root)
		stack_push(&node_stack, root);
	while(!stack_is_empty(node_stack))
	{

		top = stack_top(node_stack);
		if ((top->left == NULL && top->right == NULL)
			   	|| (pre != NULL && (pre == top->left || pre == top->right)))
		{
			op(top->data);
			pre = top;
			stack_pop(&node_stack);
		}
		else
		{
			if (top->right)
				stack_push(&node_stack, top->right);
			if (top->left)
				stack_push(&node_stack, top->left);

		}
	}
}

static int LevelOrder_treverse(BinTreeNode *node, int level, void (*op)(void *data))
{
	if (node == NULL)
		return 0;
	if (level == 1)
	{
		op(node->data);
		return 1;
	}
	return LevelOrder_treverse(node->left, level - 1,  op) + LevelOrder_treverse(node->right, level - 1, op);
}

void bintree_LevelOrder_treverse(BinTree *tree, void (*op)(void *data))
{
	int dep = bintree_depth(*tree);
	int level;
	for (level = 1; level <= dep; ++level)
		LevelOrder_treverse(tree->root, level, op);
}

void bintree_levelorder_treverse(BinTree *tree, void (*op)(void *data))
{
	BinTreeNode *root = tree->root;
	BinTreeNode *front;
	Queue	node_queue;

	queue_init(&node_queue, NULL);
	if (root)
		queue_enque(&node_queue, root);
	while (!queue_is_empty(node_queue))
	{
		front = queue_front(node_queue);
		op(front->data);
		queue_deque(&node_queue);

		if (front->left) 
			queue_enque(&node_queue, front->left);
		if (front->right) 
			queue_enque(&node_queue, front->right);
	}
	queue_destroy(&node_queue);
}

static int depth(BinTreeNode *node)
{
	int ldep, rdep;
	if (node)
	{
		ldep = depth(node->left);
		rdep = depth(node->right);
		return (ldep >= rdep ? ldep + 1 : rdep + 1);
	}
	else 
		return 0;
}

int  bintree_depth(BinTree tree)
{
	return depth(tree.root);
}
