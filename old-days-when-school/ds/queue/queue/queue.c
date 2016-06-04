#include "queue.h"
#include <stdlib.h>

void	InitQueue (Queue *Q)
{ 
	if ((*Q = malloc (sizeof (struct Queue))) == NULL)
		err_sys("malloc error");
	(*Q)->Rear  = NULL;
	(*Q)->Front = NULL;
}
int   IsEmptyQueue(const Queue Q)
{
	return Q->Front == NULL; 
}
void  EnQueue(const QElemType x, Queue *Q)
{
	PtrToQNode	cur;
	if ((cur = malloc (sizeof (struct QNode))) == NULL)
		err_sys("malloc error");
	cur->Elem = x;	
	cur->Prev = NULL;
	cur->Next = NULL;
	if (IsEmptyQueue(*Q))
		(*Q)->Front = (*Q)->Rear = cur;		
	else{
		cur->Prev = (*Q)->Rear;
		(*Q)->Rear->Next = cur;
		(*Q)->Rear = cur;
	}
}
void  DeQueue(Queue	*Q)
{
	PtrToQNode del;

	if (IsEmptyQueue(*Q))
		err_quit("DeQueue with a empty Queue");
	del = (*Q)->Front;
	(*Q)->Front = (*Q)->Front->Next;
//	(*Q)->Front->Prev = NULL;
	free(del);
}
QElemType Front(const Queue Q)
{
	if (IsEmptyQueue(Q))
	{
		perror("Front on a empty Queue");
		exit(EXIT_FAILURE);
	}
	return Q->Front->Elem;
}
void  ClearQueue(Queue *Q)
{
	PtrToQNode cur, del = (*Q)->Front;
	while(del)
	{
		cur=del->Next;
		free(del);
		del = cur;
	}
	(*Q)->Front = NULL;
	(*Q)->Rear = NULL;
}
void  DestoryQueue(Queue *Q)
{
	PtrToQNode cur, del = (*Q)->Front;
	while(del)
	{
		cur=del->Next;
		free(del);
		del = cur;
	}
	free(*Q);
}
