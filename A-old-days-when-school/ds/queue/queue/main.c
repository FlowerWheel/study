#include "../apue.h"
#include "queue.h"

int main (void)
{
	int		i;
	int		front;
	Queue	Q;
	
	InitQueue (&Q);

	printf("%d\n", IsEmptyQueue(Q));

	EnQueue(1, &Q);
	EnQueue(1, &Q);

	printf("%d\n", IsEmptyQueue(Q));

	front = Front(Q);

	printf("%d\n", front);

	DeQueue(&Q);

	printf("%d\n", IsEmptyQueue(Q));

	DestoryQueue(&Q);

	return 0;
}
