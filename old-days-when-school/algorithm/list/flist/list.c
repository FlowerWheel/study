#include	<stdlib.h>
#include	<string.h>

#include    "list.h"

/*
 * Define Interface for List
 */

/*Init list*/
void list_init(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->match = NULL;
	list->head = NULL;
	list->tail = NULL;
	return ;
}

/*Destroy list*/
void list_destroy(List *list)
{
	void *data;
	while (list_size(*list) > 0)
		if (list_remove_next(list, NULL, (void**)&data) == 0 
				&& list->destroy != NULL)
			list_destroy(data);
	memset(list, 0, sizeof(list));
	return ;
}

/*Insert element to list*/
int  list_insert_next(List *list, Position pos, const void *data)
{
	ListElmt	*new_element;
	if ( (new_element = malloc(sizeof(ListElmt))) == NULL)
		return -1;
	new_element->data = (void *)data;
	if (pos == NULL)
	{// insert new element at list head
		if (list_size(*list) == 0) //if list is empty
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{// insert new element behind element
		if (pos->next == NULL) //if element is tail
			list->tail = new_element;
		new_element->next = pos->next;
		pos->next = new_element;
	}
	++(list->size);
	return 0;
	
}
int  list_remove_next(List *list, Position pos, void **data)
{
	ListElmt	*old_element;
	if (list_size(*list) == 0)
		return -1;
	if (pos == NULL)
	{// remove the first element from the list
		if (data)
			*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(*list) == 1) //if only one node
			list->tail = NULL; //
	}
	else 
	{// remove the elem who behin element
		if (pos->next == NULL) //if pos is the last node
			return -1;
		if (data)
			*data = pos->next->data;
		old_element = pos->next;
		pos->next = pos->next->next;

		if (pos->next == NULL) //if pos become the last node
			list->tail = pos; //
	}
	free(old_element);
	--(list->size);
	return 0;
}

void list_traverse(List list, void (*op)(void *data))
{
	Position	pos;
	if (list_size(list) == 0)
		return ;
	pos = list.head;
	do {
		op( pos->data );
		pos = pos->next;
	} while(pos != NULL);

}

Position list_search(List list, const void *key, int (*compare)(const void *key1, const void *key2))
{
	Position	pos;
	if (list_size(list) == 0)
		return NULL;
	pos = list.head;
	do {
		if ( compare( pos->data, key ) )
			return pos;
		pos = pos->next;
	} while(pos != NULL);
	return NULL;
}

void list_reverse(List *list)
{
	void		*save_data;
	Position	cur;
	if (list_size(*list) < 1)
		return ;
	cur = list->head;
	do {
		list_remove_next(list, cur, &save_data);
		list_insert_next(list, NULL, save_data);
	} while (cur->next != NULL);


}

Position list_middle(List list)
{
	Position p1, p2;
	if (list_size(list) == 0)
		return NULL;
	p1 = p2 = list.head;
	while(p2->next)
	{
		p2 = p2->next;
		if (p2->next)
		{
			p2 = p2->next;
			p1 = p1->next;
		}
	}
	return p1;
}
