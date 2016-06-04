#ifndef  QUEUE_H
#define  QUEUE_H

#include <stdlib.h>
#include "list.h"

typedef List Queue;

#define queue_init list_init
#define queue_destroy list_destroy

#define queue_peek(queue) ( (queue).head == NULL ? NULL : (queue).head->data)
#define queue_size list_size
#define queue_front queue_peek
#define queue_is_empty list_is_empty

int queue_enque(Queue *queue, const void *data);
int queue_deque(Queue *queue);


#endif  /*QUEUE_H*/
