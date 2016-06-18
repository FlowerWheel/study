#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "lueap.h"
#include "type.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/errno.h>

#include "queue.h"

struct QNode{
	struct QNode	*Prev;
	QElemType		Elem;
	struct QNode	*Next;
};

typedef struct QNode *PtrToQNode;
typedef struct Queue *PtrToQueue, *Queue;

struct Queue{
	PtrToQNode  Front;
	PtrToQNode	Rear;
};

void  InitQueue(Queue *Q);
int   IsEmptyQueue(Queue Q);
void  EnQueue(const QElemType x, Queue *Q);
void  DeQueue(Queue	*Q);
QElemType Front(const Queue Q);
void  ClearQueue(Queue *Q);
void  DestoryQueue(Queue *Q);

#endif /*_QUEUE_H_*/
