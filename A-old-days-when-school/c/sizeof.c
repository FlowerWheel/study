#include <stdio.h>
#include <stdlib.h>

/*
 * 在结构体或联合体类型中，如果只有一个char类型，那么sizeof(char)=sizeof(struct);
 * 如果还包含有其他类型，那么char类型会自动对其到机器子宽, 即char与int占有同样大小的存储区。
 */
int main (void)
{
	int len;
	struct st{
		int i;
	//	char c;
		float f;
		double d;
	};

	struct ST{
		int I;
		char C;
		float F;
		double D;
		union {
			short s;
			char ch;
			int	i;
		//	double d;
		};
	};

	struct achar{
		char ch;
		double asdf;
	};

	struct aunion{
		int qwer;
		union {
			char as;
		};
	};

	len = sizeof si;
	printf("%d\n", sizeof si);
	printf("%d\n", len);
	len = sizeof (int);
	printf("%d\n", len);
	printf("%d, %d, %d, %d, %d, %d\n",
		   	sizeof(short), sizeof(int), sizeof(long), sizeof(char), sizeof(float), sizeof(double));
	printf("%d\n", sizeof(struct st));
	printf("%d\n", sizeof(struct ST));
	printf("%d\n", sizeof(struct achar));
	printf("%d\n", sizeof(struct aunion));
	return 0;	
}
