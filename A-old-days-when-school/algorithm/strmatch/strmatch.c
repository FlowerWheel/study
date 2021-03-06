#include	"strmatch.h"
#include	<string.h>

int simple_string_match(char *T, char *P)
{
	size_t		m, n;
	int			i, s;
	
	n = strlen(T);
	m = strlen(P);
     
    if (m > n)
        return 0;

	for (s = 0; s < n - m + 1; ++s)
	{
		for (i = 0; i < m; ++i)
			if (T[s + i] != P[i])
				break;
		if (i == m)
			break;
	}
	if (s == n - m + 1 && i != m)
		return 0;
	return ++s;
}

int simple_match(const char *s, const char *p, int pos)
{
	int i = pos;
	int j = 0;
	while (s[i] != '\0' && p[j] != '\0'){
		if (s[i] == p[j])
			++i, ++j;
		else
			i = i - j + 1, j = 0;
	}
	if (p[j] == '\0')
		return i - j;
	else 
		return -1;
}

int	rk_string_match(char *T, char *P, int d, int q)
{
	int s = 0;
	return s;
}

int match_kmp(const char * s ,const char * p,int pos) {
    int next[11] ;
    int i = pos ;
    int j = 0 ;
    continue_prefix_function(p,next) ;
    while(s[i] != '\0' && p[j] != '\0') {
        if(s[i] == p[j]) {
            i ++ ;
            j ++ ;
        }else {
            if(next[j] == -1) {
                i ++ ;
                j = 0 ;
            }
            else {
                j = next[j] ;
            }
        }
    }
    if(p[j] == '\0')
        return i - j ;
    else
        return -1 ;
}
