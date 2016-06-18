#include	"avltree.h"
#include	<stdio.h>

void print_data(void *data)
{
	printf("%d ", *(int*)data);
}

int main (void)
{
	Elmt		v;
	int			i;
	AvlTree		avlt;

	avltree_init(&avlt, NULL);

	for( i = 0 ; i < 10 ; ++i )
	{
		avltree_insert(&avlt, i);
//		printf("depth : %d\n", avltree_depth(avlt));
	}
	
	v = avltree_findMax(&avlt);
	printf("Max : %d\n", v);

	v = avltree_findMin(&avlt);
	printf("Min : %d\n", v);

	avltree_inorder_treverse(&avlt, print_data);
	printf("\n");
	avltree_levelorder_treverse(&avlt, print_data);
	printf("\n");

	for( i = 0 ; i < 9; ++i )
	{
		avltree_remove(&avlt, i);
		printf("size : %d\n", avltree_size(avlt));
		avltree_inorder_treverse(&avlt, print_data);
		printf("\n");
		avltree_levelorder_treverse(&avlt, print_data);
		printf("\n");
	}
		
	printf("depth : %d\n", avltree_depth(avlt));

	avltree_inorder_treverse(&avlt, print_data);
	printf("\n");

	avltree_levelorder_treverse(&avlt, print_data);
	printf("\n");
	avltree_destroy(&avlt);
	return 0;
}
