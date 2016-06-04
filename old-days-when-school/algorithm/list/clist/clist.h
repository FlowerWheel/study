#ifndef  CLIST_H
#define  CLIST_H

#include    <stdlib.h>

/*Define List Element*/
typedef struct _CListElmt{
	void				*data;
	struct _CListElmt	*next;
}CListElmt;

/*Define List*/
typedef struct _CList{
	int		size;
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);
	CListElmt *head;
	CListElmt *tail;
}CList;

/*Define Interface for List*/
void clist_init(CList *list, void (*destroy)(void *data));
void clist_destroy(CList *list);
int  clist_insert_next(CList *list, CListElmt *element, const void *data);
int  clist_remove_next(CList *list, CListElmt *element, void **data);

#define clist_size(list) ( (&list)->size )
#define clist_is_empty(list) ( (&list)->size == 0 ? 1 : 0 )
#define clist_head(list) ( (&list)->head )
#define list_element_data(element) ( (&element)->data )
#define list_element_next(element) ( (&element)->next )

#endif  /*LIST_H*/
