#include "stack.h"

int main(void)
{
	int	 status;
	Stack s;
	ElemType e;

//	s = CreatStack();
	InitStack(&s);

	status = IsEmptyStack(s);
	printf("empty : %d\n", status);

	e = 1;
	Push(e, s);

	e = 2;
	Push(e, s);

	status = IsEmptyStack(s);
	printf("empty : %d\n", status);
	
	e = Top(s);
	printf("top : %d\n", e);

	Pop(&s);

	e = Top(s);
	printf("top : %d\n", e);

	Pop(&s);
	ClearStack(&s);

	e = 2;
	Push(e, s);

	e = Top(s);
	printf("top : %d\n", e);

	ClearStack(&s);
	status = IsEmptyStack(s);
	printf("empty : %d\n", status);
	
	DestoryStack(&s);

	return 0;
}
