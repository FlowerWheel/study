#include "cclklist.h"

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
	e = 10;
	pos = FindIndex(e, test);
	printf("pos :%d\n", pos);
	ptr = Locate(pos, test);
	printf("ptr :%p\n", ptr);
	pos ++;
	ptr = LocatePrevious(pos, test);
	printf("ptr :%p\n", ptr);
	for (e = 8; e <= 12; e++)
		Deletei(6, &test);
	Traverse(test, NULL);
	len = Length(test);
	printf("len :%d\n", len);
	DeleteList(&test);
	return 0;
}
