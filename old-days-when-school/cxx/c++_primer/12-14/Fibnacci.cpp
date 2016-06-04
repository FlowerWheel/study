#include <stdio.h>
#include <wchar.h>

template <long long depth>
class Fibnacci
{
	public:
		static const long long value = Fibnacci<depth-1LL>::value + Fibnacci<depth-2LL>::value;
};

template <>
class Fibnacci<0LL>
{

	public:
		static const long long value = 0;
};

template <>
class Fibnacci<1LL>
{

	public:
		static const long long value = 1;
};

template <long long depth>
void printFibnacci()
{

	printFibnacci<depth-1LL>();
	wprintf(L"%lld\n",  Fibnacci<depth>::value);
}

template <>
void printFibnacci<0LL>()
{

	wprintf(L"%lld\n",  Fibnacci<0LL>::value);
}

int main()
{

	printFibnacci<92LL>();
	return 0;
}
