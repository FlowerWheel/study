#include "type.h"
#include "stack.h"
#include "lueap.h"

Stack CreatStack(void)
{
	Stack	s;
	if ((s = malloc(sizeof(struct SNode))) == NULL)
		err_sys("malloc error");
	s->Next = NULL;
	return s;
}
void  InitStack(Stack *s)
{
	if ((*s = malloc(sizeof(struct SNode))) == NULL)
		err_sys("malloc error");
	(*s)->Next = NULL;

}
int	  IsEmptyStack(const Stack s)
{
	return s->Next == NULL;
}
void  Push(const SElemType x, Stack *s)
{
	PtrToSNode	add;
	if ((add = malloc(sizeof (struct SNode))) == NULL)
		err_sys("malloc error");
	add->Elem = x;
	add->Next = (*s)->Next;
	(*s)->Next = add;
}
SElemType Top(const Stack s)
{
	if (IsEmptyStack(s))
		err_quit("top on a stack empty");
	return s->Next->Elem;
}
void Pop(Stack *s)
{
	PtrToSNode	del;
	if (IsEmptyStack(*s))
		err_quit("pop on a stack empty");
	del = (*s)->Next;
	(*s)->Next = del->Next;
	free (del);
}
void  ClearStack(Stack *s)
{
	PtrToSNode	del, cur = (*s)->Next;
	(*s)->Next = NULL;
	while (cur)
	{
		del = cur;
		cur = cur->Next;
		free(del);
	}
}
void  DestoryStack(Stack *s)
{
	PtrToSNode	del;
	while (*s)
	{
		del = *s;
		*s = (*s)->Next;
		free(del);
	}
}
