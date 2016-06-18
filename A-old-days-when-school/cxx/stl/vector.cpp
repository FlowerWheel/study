#include <iostream>
#include <vector>

using namespace std;

#define		N    100

int main (void)
{
	int			temp[N] = {0};
	vector<int>  v1(N);

	v1.assign(temp, temp + N);
	v1.assign(N, 1);

	cout << "*********************Use iterator*********************" << endl;
	cout << "begin()  end()" << endl;
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		cout << *it << " " ;

	cout << "rbegin()  rend()" << endl;
	for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++)
		cout << *it << " " ;
	cout << endl;

	cout << "cbegin()  cend()" << endl;
	for (auto it = v1.cbegin(); it != v1.cend(); it ++)
		cout << *it << " " ;
	cout << endl;

	cout << "crbegin()  crend()" << endl;
	for (auto it = v1.crbegin(); it != v1.crend(); it ++)
		cout << *it << " " ;
	cout << endl;

	cout << "size() : "			<< v1.size() << endl;
	cout << "max_size() : "		<< v1.max_size() << endl;
	cout << "resize() : ";		v1.resize(80);
	cout << "size() : "			<< v1.size() << endl;
	cout << "capacity() : "		<< v1.capacity() << endl;
	cout << "resize() : " << endl;	
	v1.resize(100, 100);
	cout << "capacity() : "		<< v1.capacity() << endl;
	cout << "empty() : "		<< v1.empty() << endl;
	cout << "reserve() : ";		v1.reserve(80);
	cout << "shrink_to_fit : "; v1.shrink_to_fit();
	cout << "size() : "			<< v1.size() << endl;

	cout << "front() : " << v1.front() << endl;
	cout << "back() :  " << v1.back() << endl;
	

	int *p = v1.data();
	for (unsigned int i = 1; i <= v1.size(); i++, p++)
//		*p = i;

	v1.push_back(1111);
	v1.pop_back();

	
	for (unsigned int i = 0; i < v1.size(); i++)
		cout << v1.at(i) << " ";
	cout << endl;

	for (unsigned int i = 0; i < v1.size(); i++)
		v1.at(i) = i;
/*
	cout << "Use [] visit : " << endl;
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";
	cout << endl;

	cout << "Use at() visit : " << endl;
	for (int i = 0; i < v1.size(); i++)
		cout << v1.at(i) << " ";
	cout << endl;

//	v1.resize();
//	v1.swap(v2);

	v1.clear();
	cout << "Use size() : " << v1.size() << endl;
	cout << v1.empty() << endl;
	*/

	return 0;

}
