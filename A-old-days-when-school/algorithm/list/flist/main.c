#include	"list.h"

#include	<stdio.h>

#define ELEM_NUM 4

void print (void *data)
{
	printf("%d ", *(int *)data);
}

int compare (const void *key1, const void *key2)
{
	if ( *(int*)key1 == *(int*)key2 )
		return 1;
	else 
		return 0;
}

int main (void)
{
	int		i;
	int		elem[ELEM_NUM];
	int		size;
	int		isempty;

	List	list;

	list_init(&list, NULL);
///////////////////////////////////////////////////
	isempty = list_is_empty(list);
	printf("empty ? %d\n", isempty);
	size = list_size(list);
	printf("size = %d\n", size);

	for (i = 0; i < ELEM_NUM; ++i) {
		elem[i] = i + 1;
		list_insert_next(&list, NULL, &elem[i]);
	}

	isempty = list_is_empty(list);
	printf("empty ? %d\n", isempty);
	size = list_size(list);
	printf("size = %d\n", size);
///////////////////////////////////////////////////

/*
	Position pos = NULL;
	pos = list_middle(list);
	if (pos != NULL)
		printf ("pos = %p, data = %d\n", pos, (int)*(int*)(pos->data));
*/

	list_traverse(list, print);
	printf("\n");

	list_reverse(&list);

	list_traverse(list, print);
	printf("\n");

	list_destroy(&list);

	return 0;
}
