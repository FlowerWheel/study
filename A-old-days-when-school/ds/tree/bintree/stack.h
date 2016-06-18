#ifndef _STACK_H_
#define _STACK_H_

#include "lueap.h"
#include "type.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/errno.h>

#include "stack.h"

struct  SNode{
	SElemType		Elem;
	struct SNode	*Next;
};

typedef struct SNode *PtrToSNode, *Stack;

Stack CreatStack(void);
void  InitStack(Stack *s);
int	  IsEmptyStack(const Stack s);
void  Push(const SElemType x, Stack *s);
SElemType Top(const Stack s);
void  Pop(Stack *s);
void  ClearStack(Stack *s);
void  DestoryStack(Stack *s);

#endif /*_STACK_H_*/
