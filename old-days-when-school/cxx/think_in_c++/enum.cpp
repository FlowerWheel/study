#include	<iostream>
using namespace std;

enum I{
	a, b, c, d
};

int main (void)
{
	I	i[10]	= {b};
	for (int j = 0; j < 10; ++j)
		cout << i[j]<< endl;
	cout << sizeof(I) << endl;
	return 0;
}
