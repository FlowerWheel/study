#include <cstring>
#include <iostream>
using namespace std;

#define N 100
#define M 10
const int prm[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

int allCombineNum(char* str );
void prime(int n);
int factorial(int n);
int quick_power(int n, int exponent);

int main(void)
{
	factorial(10);
	return 0;
}

int allCombineNum(char* str)
{
	if (str == NULL)
		return 0;
	char* pos = str;
	int len = 0;
	while (*pos++)
		++len;
	if ( len == 0 )
		return 0;
	int same = 0;
	for(int i = 1; i < len; ++i)
		if (str[i-1] == str[i])
			++same;
	len = factorial(len);
	same = factorial(same);
	return (len/same);
}

void prime(int n)
{
	int arr[N];
	memset(arr, 0, sizeof(int)*N);
	cout<<"{ ";
	for(int i = 2; i < n; ++i) {
		if(!arr[i]) {
			cout<<i<<",  ";
			for(int j = i*2; j < n; j += i)
				arr[j] = 1;
		}
	}
	cout<<"}"<<endl;
}

int factorial(int n)
{
	if ( n == 0 )
		return 1;
	if ( n == 1 || n == 2)
		return n;
	int aux[M];
	memset(aux, 0, sizeof(int)*M);
	int i = 0;
	int base;
	int ret;
	while (prm[i] <= n)
	{
		ret = 0;
		base = prm[i];
		while (base <= n) {
			ret += n/base; 
			base *= prm[i];
		}
		aux[i++] = ret;
	}
	ret = 1;
	for (int i = 0; i < M; ++i)
		if(aux[i] > 0)
			ret *= quick_power(prm[i], aux[i]);
	return ret;
}

int quick_power(int n, int exponent)
{
	int ret = 1;
	while (exponent) {
		if(exponent & 1)
			ret *= n;
		n *= n;
		exponent >>= 1;
	}
	return ret;
}
