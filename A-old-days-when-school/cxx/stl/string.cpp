#include <iostream>
#include <string>

using namespace std;

int main (void)
{
	string s0("Initial String");
	string s1;
	string s2(s0);
	string s3(s0, 8, 3);
	string s4("A character sequence", 6);
	string s5("Another character sequence");
	string s6(10, 'x');
	string s7a(10, 42);
	string s7b(s0.begin(), s0.begin() + 7);
	string s8(s0 + s6);

	cout << s0 << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
	cout << s7a << endl;
	cout << s7b << endl;
	cout << s8 << endl;

	string s = s0;
	cout << "The size of s : " << s.size() << endl;
	cout << "The length of s : " << s.length() << endl;
	cout << "The max_size : " << s.max_size() << endl;
	s.resize(100);
	cout << "The capacity is : " << s.capacity() << endl;
	s.resize(7);
	s.shrink_to_fit();
	cout << "The capacity is : " << s.capacity() << endl;

	cout << "front : " << s.front() << endl;
	cout << "back : " << s.back() << endl;
	cout << "at :" << s.at(3) << endl;
	cout << "[] :" << s[3] << endl;

	s += "!!!!!";
	s += '~';
	s += s0;
	cout << "after += : " << s << endl;

	string str("abcdefghijk");
	s.append(str);
	s.append(" ");
	s.append(str, 5, 5);
	s.append(" ");
	s.append("ABCDEFG", 5);
	s.append(" ");
	s.append(10u, '.');
	s.append(" ");
	s.append(str.begin(), str.end());
	s.append(" ");
	s.append<int>(5, 0x2c);
	cout << "after append : " << s << endl;

	s.push_back('I');
	cout << "after push_back : " << s << endl;
	s.pop_back();
	cout << "after pop_back : " << s << endl;

	s.clear();
	s.empty() ? cout << "YES" : cout << "NO";
	cout << endl;
	s.resize(20, '+');
	cout << "s contains : " << s << endl;
	s.resize(14);
	cout << "s contains : " << s << endl;

	return 0;
}
