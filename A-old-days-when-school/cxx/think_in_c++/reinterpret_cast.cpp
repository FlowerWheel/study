#include	<iostream>

using namespace std;

const int	sz = 100;

struct X {
	void			f(void);
	long long		a[sz];
	int		b[sz];
};

void print(X* x)
{
	for (int i = 0; i < sz; ++i)
		cout << x->a[i] << ' ';
	cout << endl << endl;
	for (int i = 0; i < sz; ++i)
		cout << x->b[i] << ' ';
	cout << endl << "---------------------------------------------------------------------------------------" << endl;
}

int main (void)
{
	X	x;
	print(&x);

	int *xp = reinterpret_cast<int *>(&x);
	for (int *p = xp; p < xp + sz; ++p)
		*p = 0;

	print(&x);
	print(reinterpret_cast<X*>(xp));

	cout << sizeof(X) << endl;
	return 0;
}
