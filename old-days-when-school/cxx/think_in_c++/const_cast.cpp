#include	<iostream>
using namespace std;

int main (void)
{
	const int	i = 0;
	int			*j= (int*)&i; 
	/* int			*j= &i; */

	j = const_cast<int*>(&i);
	volatile int k = 0;
	int *u = const_cast<int*>(&k);
	return 0;
}
