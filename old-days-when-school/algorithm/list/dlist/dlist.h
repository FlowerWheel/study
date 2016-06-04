#ifndef  DLIST_H
#define  DLIST_H

#include    <stdlib.h>

/*Define List Element*/
typedef struct _DListElmt{
	void				*data;
	struct _DListElmt	*prev;
	struct _DListElmt	*next;
}DListElmt;

/*Define List*/
typedef struct _DList{
	int		size;
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);
	DListElmt *head;
	DListElmt *tail;
}DList;

/*Define Interface for List*/
void dlist_init(DList *dlist, void (*destroy)(void *data));
void dlist_destroy(DList *dlist);
int  dlist_insert_prev(DList *dlist, DListElmt *element, const void *data);
int  dlist_insert_next(DList *dlist, DListElmt *element, const void *data);
int  dlist_remove(DList *dlist, DListElmt *element, void **data);

#define dlist_size(dlist) ( (&dlist)->size )
#define dlist_is_empty(dlist) ( (&dlist)->size == 0 ? 1 : 0 )
#define dlist_head(dlist) ( (&dlist)->head )
#define dlist_tail(dlist) ( (&dlist)->tail )
#define dlist_is_head(element) ( (element)->prev == NULL ? 1 : 0 )
#define dlist_is_tail(element) ( (element)->next == NULL ? 1 : 0 )
#define dlist_elem_data(element) ( (&element)->data )
#define dlist_elem_next(element) ( (&element)->next )
#define dlist_elem_prev(element) ( (&element)->prev )

#endif  /*DLIST_H*/
