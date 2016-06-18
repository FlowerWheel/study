#include <iostream>
using namespace std;

typedef int* PINT;

int main(void)
{
	int i = 1;
	const PINT pi1 = &i;
	const int* pi2 = &i;

	*pi1 = 2;
	pi1++;		// te.cpp|13 col 5| error: increment of read-only variable ‘pi1’

	*pi2 = 2;	// te.cpp|15 col 9| error: assignment of read-only location ‘* pi2’
	pi2++;
	
	return 0;
}
