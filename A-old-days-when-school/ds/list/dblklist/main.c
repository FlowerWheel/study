#include "dblklist.h"
#include "lueap.h"

int main()
{
	int			i, pos, len;
	int			s;
	ElemType	e;
	Position	ptr;
	LinkedList	test;
	
	test = CreatList();
	s = IsEmpty(test);
	printf("empty :%d\n", s);

	len = Length(test);
	printf("before insert len :%d\n", len);

	for (i = 1; i <= 20; i++)
		Insert(i, i, test);

	len = Length(test);
	printf("arter insert len :%d\n", len);

	s = IsEmpty(test);
	printf("empty :%d\n", s);
	
	e = 11;
	pos = FindIndex(e, test);
	printf("pos :%d\n", pos);

	ptr = Locate(pos, test);
	printf("ptr :%p\n", ptr);
	
	pos ++;
	ptr = LocatePrevious(pos, test);
	printf("ptr :%p\n", ptr);

	for (i = 8; i <= 12; i++)
		Delete(i, &test);
	
	Traverse(test, NULL);
	Deletei(i, &test);

	len = 0;	
	len = Length(test);
	printf("len :%d\n", len);

	DeleteList(&test);
	
	len = Length(test);
	printf("len :%d\n", len);

	return 0;
}
