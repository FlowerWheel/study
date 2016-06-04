#include <set>
#include <iostream>

using namespace std;

bool fncomp(int lhs, int rhs){	return (lhs > rhs); }

struct classcomp 
{
	bool operator () (const int &lhs, const int &rhs) const
	{
		return (lhs < rhs);
	}
};

int main (void)
{
	int		myints[] = {60, 70, 80, 90, 100};
	set<int> first;
	set<int> second(myints, myints + 5);
	set<int> third(second);
	set<int> forth(second.begin(), second.end());
	set<int, classcomp> fifth;
	bool(*fn_pt)(int, int) = fncomp;
	set<int, bool(*)(int, int)> sixth(fn_pt);
	set<int> seventh = second;

//	seventh = set<int>();
	cout << "The size of second : " << second.size() << endl;
	cout << "The size of seventh : " << seventh.size() << endl;

	set<int> myset;
	set<int>::iterator it;
	pair<set<int>::iterator, bool> ret;

	for (int i = 1; i <= 5; i++)
		myset.insert(i * 10);

	ret = myset.insert(20);

	if (ret.second == false)
		it = ret.first;

	myset.insert(it, 25);
	myset.insert(it, 24);
	myset.insert(it, 26);

	myset.insert(myints, myints + 5);

	cout << "myset contains :";
	for (it = myset.begin(); it != myset.end(); ++it)
		cout << ' ' << *it;
	cout << endl;

	cout << "The size of myset : " << myset.size() << endl;

	it = myset.begin();
	++it;

	myset.erase(it);
	myset.erase(40);
	it = myset.find(60);
	myset.erase(it, myset.end());


	cout << "myset contains :";
	for (it = myset.begin(); it != myset.end(); ++it)
		cout << ' ' << *it;
	cout << endl;
	cout << "myset contains :";
	for (auto rit = myset.rbegin(); rit != myset.rend(); ++rit)
		cout << ' ' << *rit;
	cout << endl;

//	myset.clear();

	for (int i = 0; i <= 10; ++i)
	{
		cout << i * 10;
		if (myset.count(i * 10) != 0)
			cout << " is an emement of myset." << endl;
		else 
			cout << " isn't an emement of myset." << endl;
	}

	cout << "The size of myset : " << myset.size() << endl;
	cout << "The max_size of set is : " << myset.max_size() << endl;


	return 0;
}
