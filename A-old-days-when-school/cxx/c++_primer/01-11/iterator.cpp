#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main (void)
{
	vector<string>	vs(10, "vectorstring");
	vector<int>		vec(10, 8);
	vector<int>::iterator	iter = vec.begin();

//	iter = vs.begin();

	for (vector<int>::size_type ix = 0; ix != vec.size(); ix++)
		cout << vec[ix] << endl;
	for ( ; iter != vec.end(); iter++)
		cout << *iter << endl;
	return 0;
}
