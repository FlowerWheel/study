#include    "binsearchtree.h"
#include	<stdio.h>

void print_data(void *data)
{
	printf("%d ", *(int*)data);
}

int main (void)
{
	int			i;
	BinSTree	bst;
	Elmt		v;

	binstree_init(&bst, NULL);

	for( i = 10 ; i > 0 ; --i )
		binstree_insert(&bst, i);

	binstree_preorder_treverse(&bst, print_data);
   	printf("\n");

	for( i = 101 ; i <= 110 ; ++i ){
		binstree_insert(&bst, i);
		binstree_preorder_treverse(&bst, print_data);
		printf("\n");	
	}

	v = binstree_findMax(&bst);	
	printf("Max : %d", v);
	printf("\n");	

	v = binstree_findMin(&bst);	
	printf("Min : %d", v);
	printf("\n");	

	v = binstree_retrieve(binstree_findx_position(&bst, 20));
	printf("v : %d", v);
	printf("\n");	


	printf("bst_size : %d\n", binstree_size(bst));
	
	binstree_preorder_treverse(&bst, print_data);
	printf("\n");
	printf("\n");
	binstree_inorder_treverse(&bst, print_data);
	printf("\n");
	printf("\n");
	binstree_postorder_treverse(&bst, print_data);
	printf("\n");
	printf("\n");
	binstree_levelorder_treverse(&bst, print_data); 
	printf("\n");
	printf("\n");

	binstree_destroy(&bst);

	return 0;
}
