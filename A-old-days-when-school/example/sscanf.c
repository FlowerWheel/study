#include <stdio.h>

int main(int argc, char **argv)
{
	char	str[100];
	char	*pstr = str;
	int		i = 1234;

	sscanf("1234", "%s", str);
	
	while(*pstr)	
		printf("%c ", *pstr++);
	printf("%s\n", str);
}
