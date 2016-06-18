#ifndef _STACK_H_
#define _STACK_H_ 

#include    "lueap.h"

typedef int		ElemType;
typedef struct  SNode{
	ElemType		Elem;
	struct SNode	*Next;
}*PtrToSNode, *Stack;

Stack CreatStack(void);
void  InitStack(Stack *s);
int	  IsEmptyStack(const Stack s);
void  Push(const ElemType x, Stack s);
ElemType Top(const Stack s);
void  Pop(Stack *s);

void  ClearStack(Stack *s);
void  DestoryStack(Stack *s);

#endif /*_STACK_H_*/
