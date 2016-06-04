#include	<cstdlib>
#include    <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	const size_t array_size = 10;

	int		arr_i[array_size];

	for ( size_t ix = 0; ix != array_size; ++ix )
		arr_i[ix] = ix;

	for ( size_t ix = 0; ix != array_size; ++ix )
		cout << arr_i[ix] << endl;

	for ( int i = 0; i != array_size; ++i )
		cout << arr_i[i] << endl;

	typedef int arr_int[4];

	int ia[12][4];

	arr_int *ip = ia;

	return EXIT_SUCCESS;
}
