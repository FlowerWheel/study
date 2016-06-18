#include <stdio.h>
#include <stdlib.h>

static int i = 0;
static int j = 0;

void func1()
{
	i = 0;
	i++;
	printf("i = %d\t", i);
}
void func2()
{
	j++;
	printf("j = %d\t", j);
}
void func3()
{
	static k = 0;
	k++;
	printf("k = %d\t", k);
}

int main (void)
{
	int count;
	for (count = 0; count < 10; count++)
		func1();
	printf("\n");
	for (count = 0; count < 10; count++)
		func2();
	printf("\n");
	for (count = 0; count < 10; count++)
		func3();
	printf("\n");
	for (count = 0; count < 10; count++)
		func1();
	printf("\n");
	for (count = 0; count < 10; count++)
		func2();
	printf("\n");
	for (count = 0; count < 10; count++)
		func3();
	printf("\n");

	return 0;
}
