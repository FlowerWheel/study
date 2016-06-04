#include <vector>
#include <iostream>
using namespace std;

int main (void)
{
	vector<int> v1, v2(v1), v3(10, 9), v4(100);

//	cout << &v1 << " " << &v2 << " " << &v3 << " " << &v4 << endl; 

	return 0;
}
