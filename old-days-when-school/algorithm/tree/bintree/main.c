#include  "bintree.h"
#include  <stdio.h>

void* get_data(void)
{
	char *ch;
	if ((ch = malloc(sizeof(char))) == NULL)
		return NULL;
	scanf("%c", ch);
	if (*ch == '#' || *ch == ' ')
	{
		free(ch);
		ch = NULL;
		return NULL;
	}
	return (void*) ch;
}

void destroy_data(void *data)
{
	free(data);
	data = NULL;
}

void print_data(void *data)
{
	printf("%c", *(char*)data);
}

int main (void)
{
	BinTree		bt;

	bintree_init(&bt, destroy_data);

	//abdh###e##cf##g#i##
	bintree_preorder_create(&bt, get_data);

	printf("Recursion Treverse:\n");
	bintree_preorder_treverse(&bt, print_data);
	printf("\n");
	bintree_inorder_treverse(&bt, print_data);
	printf("\n");
	bintree_postorder_treverse(&bt, print_data);
	printf("\n");

	printf("nonRecursion Treverse:\n");
	bintree_nonrecursion_preorder_treverse(&bt, print_data);
	printf("\n");
	bintree_nonrecursion_inorder_treverse(&bt, print_data);
	printf("\n");
	bintree_nonrecursion_postorder_treverse(&bt, print_data);
	printf("\n");

	printf("Level Order Treverse:\n");
	bintree_levelorder_treverse(&bt, print_data);
	printf("\n");
	bintree_LevelOrder_treverse(&bt, print_data);
	printf("\n");

	bintree_destroy(&bt);

	return 0;
}
