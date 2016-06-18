#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define N 10

void allCombine(char* str);
void helper(char ch[], char aux_str[], int aux[], int n,  int len,  int cur);

int main(void)
{
	char str[] = "abab";
	allCombine(str);
	return 0;
}

void allCombine(char* str)
{
	if ( str == NULL )
		return ;
	int len = 0;
	char* pos = str;
	while (*pos++)
		++len;
	if ( len == 0 )
		return ;
	sort(str, str+len);
	int i, j;
	char ch[N];
	char aux_str[N];
	int aux[N];
	memset(aux, 0, sizeof(int)*N);
	ch[0] = *str;
	aux[0] = 1;
	for (i = 1, j = 0; i < len; ++i)
	{
		if (str[i-1] != str[i])
			ch[++j] = str[i];
		++aux[j];
	}
	helper(ch, aux_str, aux, len, j+1, 0);

}
void helper(char ch[], char aux_str[], int aux[], int n, int len, int cur)
{
	if (cur == n){
		for(int i = 0; i < n; ++i)
			cout<<aux_str[i];
		cout<<endl;
		return ;
	}
	for (int i = 0; i < len; ++i) {
		if (aux[i]){
			aux_str[cur] = ch[i];
			--aux[i];
			helper(ch, aux_str, aux, n, len, cur+1);
			++aux[i];
		}
	}
}


