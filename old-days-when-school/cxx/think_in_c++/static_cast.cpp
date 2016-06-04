#include	<iostream>

using namespace std;

void	func(int){}

int main (void)
{
	int		i = 0x7fff;
	long	l;
	float	f;

	l = i;
	f = i;

	l = static_cast<long>(i);
	f = static_cast<float>(i);

	i = l;
	i = f;

	i = static_cast<int>(l);
	i = static_cast<int>(f);

	char c = static_cast<char>(i);

	void	*vp = &i;
	float	*fp = (float*)vp;
	fp	= static_cast<float*>(vp);

	double	d = 0.0;
	int		x = d;
	x = static_cast<int>(d);

	func(d);
	func(static_cast<int>(d));

	return 0;
}
