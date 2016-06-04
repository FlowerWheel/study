#include <stdio.h>
#include <stdlib.h>

struct st{
	char ch;
	int asf;
	long ln;
};

void func(int v[100])
{
	printf("sizeof (v) = %d\n", sizeof(v)); // 4
}
int main (void)
{
	char *p =NULL;
	int a[100] = {0};
	
	struct st *stPtr;
	printf("sizeof(struct st) =%d\n", sizeof(struct st));
	printf("sizeof(stPtr) =%d\n", sizeof(stPtr));
	printf("sizeof(*stPtr) =%d\n", sizeof(*stPtr));
	printf("sizeof(p) = %d\n", sizeof(p));
	printf("sizeof(&p) = %d\n", sizeof(&p));
	printf("sizeof(*p) = %d\n", sizeof(*p));
	printf("sizeof(a) = %d\n", sizeof(a));
	printf("sizeof(a[100]) = %d\n", sizeof(a[100]));
	printf("sizeof(&a) = %d\n", sizeof(&a));
	printf("sizeof(a[0]) = %d\n", sizeof(a[0]));
	printf("sizeof(&a[0]) = %d\n", sizeof(&a[0]));
	printf("a = %p, a[0] = %d, a[100] = %d\n", a, a[0], a[100]);

	func(a);//传地址

	return 0;
}
