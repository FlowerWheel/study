#include "queue.h"
#include "list.h"

int queue_enque(Queue *queue, const void *data)
{
	return list_insert_next(queue, list_tail(*queue), data);
}

int queue_deque(Queue *queue)
{
	return list_remove_next(queue, NULL, NULL);
}
