#include <iostream>
#include <string>
using namespace std;

int main (void)
{
	string	s1, s2;
	
	cin >> s1 >> s2;
	cout << s1 << s2 << endl;

	string line;
	while (getline(cin, line))
		cout << line << endl;
	return 0;
}
