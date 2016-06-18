#include	"strmatch.h"
#include	<stdio.h>

int main (void)
{
	char	*t = "123456789";
	char	*p = "2";
	int		s;

	//s = simple_string_match(t, p);
	s = simple_match(t, p, 0);

	printf("s = %d\n", s);
	return 0;
}
