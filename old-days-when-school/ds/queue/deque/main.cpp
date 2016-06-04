#include "Queue.h"
#include <iostream>

using namespace std;

int main()
{
	Queue <char> Q;
	for ( int i = 0 ; i < 10 ; i ++ )
		Q.push('a'+i);
	for ( int i = 1 ; i < 10 ; i ++ )
	{
		cout << Q.top() << endl;
		Q.pop();
	}
	return EXIT_SUCCESS;
}
