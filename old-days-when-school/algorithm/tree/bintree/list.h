#ifndef  LIST_H
#define  LIST_H

#include    <stdlib.h>

/*Define List Element*/
typedef struct _ListElmt{
	void				*data;
	struct _ListElmt	*next;
}ListElmt, *Position;

/*Define List*/
typedef struct _List{
	int			size;
	ListElmt	*head;
	ListElmt	*tail;
	int			(*match)(const void *key1, const void *key2);
	void		(*destroy)(void *data);
}List;

/*Define Interface for List*/
void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);

int  list_insert_next(List *list, Position pos, const void *data);
int  list_remove_next(List *list, Position pos, void **data);

void list_traverse(List list, void (*op)(void *data));

Position list_search(List list, const void *key, int (*compare)(const void *key1, const void *key2));

void list_reverse(List *list);

Position list_middle(List list);

void list_sort(List *list);

void list_merge(List *list1, List *list2);

#define list_size(list) ( (list).size )
#define list_is_empty(list) ( (list).size == 0 ? 1 : 0 )
#define list_head(list) ( (list).head )
#define list_tail(list) ( (list).tail )
#define list_element_data(element) ( (element).data )
#define list_element_next(element) ( (element).next )
#define list_is_head(list, element) ( (list).head == element ? 1 : 0 )
#define list_is_tail(list, element) ( (list).tail == element ? 1 : 0 )

#endif  /*LIST_H*/
