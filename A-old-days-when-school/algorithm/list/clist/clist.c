#include	<stdlib.h>
#include	<string.h>

#include    "clist.h"

/*
 * Define Interface for List
 */

/*Init list*/
void clist_init(CList *list, void (*destroy)(void *data));
void clist_destroy(CList *list);
int  clist_insert_next(CList *list, CListElmt *element, const void *data);
int  clist_remove_next(CList *list, CListElmt *element, void **data);


