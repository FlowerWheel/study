#include	<iostream>

using namespace std;

class Bool{
	bool	a, b;
};

int main (void)
{
	std::cout << sizeof(bool) << std::endl;
	std::cout << sizeof(Bool) << std::endl;
	return 0;
}
