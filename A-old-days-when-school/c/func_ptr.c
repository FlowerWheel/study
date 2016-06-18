#include	<stdio.h>

void function()
{
	printf("Call Function\n");
}

int main (void)
{
	void (*pf)();

	*(int*)&pf = (int)function;

	(*pf)();

//	(*(void(*)())0)();
	(*(void(*)())function)();
	(*(void(*)())&function)();

	return 0;
}
