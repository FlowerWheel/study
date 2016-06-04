#include <iostream>
#include <string>
#include <cctype>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main (void)
{
	string str("abcdefg");
	for (string::size_type ix = 0; ix != str.size(); ++ix)
	{
		cout << str[ix] << " " ;
		str[ix]++;
	}
	cout <<endl;
	for (string::size_type ix = 0; ix != str.size(); ++ix)
		cout << str[ix] << " " ;
	cout <<endl;

	cout << "C-Style string" << endl;
	const char *cstr = str.c_str();
	cout << cstr << endl;

/*
	string	s1, s2(s1), s3("abcdefg"), s4(10, 'c');
	cout << &s1 << endl;
	s1 = s3;
	cout << &s1 << endl;
	cout << s1 << endl;
	cout << s1.empty() << endl;
	cout << s2.empty() << endl;

	cin >> s1 >> s2;
	cout << s1 << s2 << endl;	
	
	cout << s1.empty() << endl;
	cout << s2.empty() << endl;
	
	string  s12 = s1 + s2;
	cout << s1.size() << endl;
	cout << s2.size() << endl;
	cout << s12.size() << endl;

	cout << s12 <<endl;

//	string word;
//	while (cin >> word)
//		cout << word << endl;

//	string line;
//	while (getline(cin, line))
//		cout << line << endl;
*/
	return 0;
}
