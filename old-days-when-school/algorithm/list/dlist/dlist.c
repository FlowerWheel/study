#include	<stdlib.h>
#include	<string.h>

#include    "dlist.h"

/*
 * Define Interface for List
 */

void dlist_init(DList *dlist, void (*destroy)(void *data))
{
	dlist->size = 0;
	dlist->destroy = destroy;
	dlist->head = NULL;
	dlist->tail = NULL;
	return ;
}

void dlist_destroy(DList *dlist)
{
	void *data;
	while (dlist_size(*dlist) > 0)
		if (dlist_remove(dlist, NULL, (void **)&data) && dlist->destroy != NULL)
			dlist->destroy(data);
	memset(dlist, 0, sizeof(DList));
	return ;
}
int  dlist_insert_prev(DList *dlist, DListElmt *element, const void *data)
{
	DListElmt	*new_element;
	if (element == NULL && dlist_size(*dlist) != 0)
		return -1;
	if ((new_element = malloc(sizeof(DListElmt))) == NULL)
		return -1;
	new_element->data = (void *)data;
	if (dlist_size(*dlist) == 0)
	{
		dlist->head = new_element;
		dlist->head->prev = NULL;
		dlist->head->next = NULL;
		dlist->tail = new_element;
	}
	else
	{
		new_element->prev = element->prev;
		new_element->next = element;
		if (element->prev == NULL)
			dlist->head = new_element;
		else 
			element->prev->next = new_element;

		element->prev = new_element;
	}
	++dlist->size;
	return 0;
}
int  dlist_insert_next(DList *dlist, DListElmt *element, const void *data)
{
	DListElmt	*new_element;
	if (element == NULL && dlist_size(*dlist) != 0)
		return -1;
	if ((new_element = malloc(sizeof(DListElmt))) == NULL)
		return -1;
	new_element->data = (void *)data;
	if (dlist_size(*dlist) == 0)
	{
		dlist->head = new_element;
		dlist->head->prev = NULL;
		dlist->head->next = NULL;
		dlist->tail = new_element;
	}
	else
	{
		new_element->prev = element;
		new_element->next = element->next;
		if (element->next == NULL)
			dlist->tail = new_element;
		else 
			element->next->prev = new_element;

		element->next = new_element;
	}
	++dlist->size;
	return 0;
}
int  dlist_remove(DList *dlist, DListElmt *element, void **data)
{
	if (element == NULL || dlist_size(*dlist) == 0)
		return -1;

	*data = element->data;
	if (element == dlist->head)
	{
		dlist->head = element->next;
		if (dlist->head == NULL)
			dlist->tail = NULL;
		else 
			element->next->prev = NULL;
	}
	else 
	{
		element->prev->next = element->next;
		if (element->next == NULL)
			dlist->tail = element->prev;
		else
			element->next->prev = element->prev;
	}
	free(element);
	--dlist->size;
	return 0;
}
