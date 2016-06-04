#include "set.h"
#include "list.h"

void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
	list_init(set, destroy);
	set->match = match;
	return ;
}

int	 set_insert(Set *set, const void *data)
{
	if (set_is_member(set, data))
		return -1;
	return list_insert_next(set, set->tail, data);
}

int  set_remove(Set *set, void **data)
{
	ListElmt	*member, *prev;
	prev = NULL;
	for (member = set->head; member != NULL; member = member->next)
	{
		if (set->match(*data, member->data))
			break;
		prev = member;
	}
	if (member == NULL)
		return -1;
	return list_remove_next(set, prev, data);
}

int	 set_union(Set *setu, const Set *set1, const Set *set2)
{
	ListElmt	*member;
	void		*data;

	/* set_init(setu, set1->match, NULL); */

	for (member = set1->head; member != NULL; member = member->next)
	{
		data = member->data;
		if (set_is_member(setu, data))
			continue;
		if (list_insert_next(setu, setu->tail, data) != 0)
		{
//			set_destroy(setu);
			return -1;
		}
	}
	for (member = set2->head; member != NULL; member = member->next)
	{
		data = member->data;
		if (set_is_member(setu, data))
			continue;
		if (list_insert_next(setu, setu->tail, data) != 0)
		{
//			set_destroy(setu);
			return -1;
		}
	}
	return 0;
}

int	 set_intersection(Set *seti, const Set *set1, const Set *set2)
{
	ListElmt	*member;
	void		*data;

	for (member = set1->head; member != NULL; member = member->next)
	{
		if (set_is_member(set2, member->data))
		{
			data = member->data;
			if (list_insert_next(seti, seti->tail, data) != 0)
			{
//				set_destroy(seti);
				return -1;
			}
		}
	}
	return 0;
}
int	 set_deference(Set *setd, const Set *set1, const Set *set2)
{
	ListElmt	*member;
	void		*data;

	for (member = set1->head; member != NULL; member = member->next)
	{
		if (!set_is_member(set2, member->data))
		{
			data = member->data;
			if (list_insert_next(setd, setd->tail, data) != 0)
			{
//				set_destroy(setd);
				return -1;
			}
		}
	}
	return 0;
}

int	 set_is_member(const Set *set, const void *data)
{
	ListElmt	*member;
	for (member = set->head; member != NULL; member = member->next)
	{
		if (set->match(data, member->data))
			return 1;
	}
	return 0;
}

int	 set_is_subset(const Set *set1, const Set *set2)
{
	ListElmt	*member;

	if (set_size(set1) > set_size(set2))
		return 0;
	for (member = set1->head; member != NULL; member = member->next)
	{
		if (!set_is_member(set2, member->data))
			return 0;
	}
	return 1;
}
int	 set_is_equal(const Set *set1, const Set *set2)
{
	if (set_size(set1) != set_size(set2))
		return 0;
	return set_is_subset(set1, set2);
}
