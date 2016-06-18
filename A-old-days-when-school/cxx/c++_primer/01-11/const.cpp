#include	<iostream>
#include	"header.hpp"

/* using namespace std; */
using std::cout;
using std::endl;
using std::iostream;

extern const int i = 0;

int main (void)
{
	const double *cptr;
//	*cptr = 1;
	double	pcpter;
	cptr = &pcpter;

	const double pi = 3.141592654;
//	double *ptr = &pi;
	const double *ptr2 = &pi;
	const void *ptr3 = &pi;
	const double &refpi = pi;
	cout << &pi << " " << &refpi << endl;

	int errNumb = 0;
	int * const curErr = &errNumb;
	int errNum = 1;
//	curErr = & errNum;

	const double * const pi_ptr = &pi;
	
	int const ii = 0;

	int const * const pii = &ii;

	/* int &ref1 = 50; // error  */
	int	ref1 = 50;
	const int &ref2 = 50;
	const int &ref3 = ref1 + ref2;
	double dref1 = 1.0000;
	const int &dref2 = dref1;
	cout << "********************" << endl;
	cout << dref1 << dref2 << endl;
	cout << "********************" << endl;
	cout << iii << endl;
	return 0;
}
