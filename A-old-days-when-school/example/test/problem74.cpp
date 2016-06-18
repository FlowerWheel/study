#include <iostream>
using namespace std;

#define N 10

int getMajor(int arr[], int n);

int main(void)
{
	int arr[N] = {2, 2, 3, 2, 2, 5, 2, 6, 1, 2};
	cout<< getMajor(arr, N) <<endl;
	return 0;
}

int getMajor(int arr[], int n)
{
	int ret, cnt = 0;
	for (int i = 0; i < n; ++i)
	{
		if (cnt == 0)
			ret = arr[i], ++cnt;
		else if (arr[i] == ret)
			++cnt;
		else
			--cnt;
	}
	return ret;
}
