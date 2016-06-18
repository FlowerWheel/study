#include "table.h"

static void print(PtrToNode node)
{
	printf("%d  ", node->elem);
}

int main (void)
{
	int		i;
	Table	t;
	Initialization(&t);
	printf ("Empty : %d\n", IsEmpty(t));
	printf ("Length : %d\n", Length(t));
//	Creat (&t, GetElem);

	for (i = 1; i <= 20; i++)
		Insert_i(t, i, i);
	printf ("Length : %d\n", Length(t));
	for (i = 1; i <= 20; i++)
		Insert_p(t, Find(t,i), i);
	printf ("Length : %d\n", Length(t));
	for (i = 1; i <= 20; i++)
		Insert_p(t, Locate(t, i+1), i);
	printf ("Length : %d\n", Length(t));
	
	Traverse(t, print);
	printf("\nMakeEmpty\n");
	MakeEmpty(t);
	printf ("Length : %d\n", Length(t));
	
	Destory(&t);
	return 0;
}
