#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef int	QElemType;
typedef struct QNode{
	struct QNode	*Prev;
	QElemType		Elem;
	struct QNode	*Next;
}*PtrToQNode;

typedef struct Queue{
	PtrToQNode  Front;
	PtrToQNode	Rear;
}*PtrToQueue, *Queue;

void  InitQueue(Queue *Q);
int   IsEmptyQueue(Queue Q);
void  EnQueue(const QElemType x, Queue *Q);
void  DeQueue(Queue	*Q);
QElemType Front(const Queue Q);
void  ClearQueue(Queue *Q);
void  DestoryQueue(Queue *Q);

#endif /*_QUEUE_H_*/
