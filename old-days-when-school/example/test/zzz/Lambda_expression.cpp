/*
 * test.cpp - Lambda表达式、for_each测试
 *
 *   C++ 11标准 Lambda表达式，for_each函数模板
 *
 *             Copyright  叶剑飞  2012
 *
 *
 *  编译命令：
 *        g++ test.cpp -o test -std=c++0x -Wall
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>   // sort函数模板、for_each函数模板
#include <functional>  // function类模板

using namespace std;

#ifndef _MSC_VER
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

int main ( )
{
	int a[] = {1,2,5,9,52,6,3,14};
	function <bool (const int & , const int &)> compare;
	auto output = [](int n)->void{ cout << n << endl; };
	// C++11标准中， auto 函数新义，任意类型，类型由初始化表达式确定
	// “[](int n)->void{ cout << n << endl; }”是Lambda表达式

	cout << "升序排序" << endl;
	compare = []( const int & a , const int & b )->bool { return a < b; };
	sort( a, a+_countof(a), compare  );
	for_each( a, a+_countof(a), output );
	cout << endl;

	cout << "降序排序" << endl;
	compare = []( const int & a , const int & b )->bool { return b < a; };
	sort( a, a+_countof(a), compare  );
	for_each( a, a+_countof(a), output );
	cout << endl;

	return EXIT_SUCCESS;
}
