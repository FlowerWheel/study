#include <iostream>
#include <string>
using namespace std;

int main (void)
{
	int *pia = new int[10];
	int *pia2 = new int[20]();
	
	delete [] pia;
	delete [] pia2;

//	const int * pci_bad = new const int[100]; // error
	const int * pci_ok  = new const int[100](); // OK

//	delete [] pci_bad;
	delete [] pci_ok;

	const string *pcs = new const string[100]; // OK

	delete [] pcs;

	string *psa = new string[10];

	delete [] psa;

	int i = 0;

	while (true)
	{
		i++;
		char * c = new char;
		if (c == NULL)
			break;
	}
	cout << i << endl;

	return 0;
}
