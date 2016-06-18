#include <istream>
#include <ostream>
#include <iostream>

using namespace std;

class TypeName{
	TypeName& operator () (arg1, arg2, arg3, ...);
	friend operator >> (istream &is, TypeName &name);
	friend operator << (ostream &os, TypeName &name);

	operator = (const TypeName &name); // must return *this

	/* -> * must define as a member function of a class */
	TypeName& operator * ();
	TypeName& operator -> ();

	TypeName& operator ++();
	TypeName& operator --();

	TypeName& operator ++(int);
	TypeName& operator --(int);
};

/* + += - -+ * *= / /= */
TypeName operator + (const TypeName &lhs, const TypeName &rhs);
TypeName operator += (const TypeName &lhs, const TypeName &rhs);

bool operator == (const TypeName &lhs, const TypeName &rhs);
bool operator != (const TypeName &lhs, const TypeName &rhs);
bool operator < (const TypeName &lhs, const TypeName &rhs);
bool operator <= (const TypeName &lhs, const TypeName &rhs);
bool operator > (const TypeName &lhs, const TypeName &rhs);
bool operator >= (const TypeName &lhs, const TypeName &rhs);
