#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void swap(char *s, int i, int j)
{
	char tmp;

	if (i == j)	
		;
	else {
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}


void combine(char *s, int low, int high)
{
	int		i;

	if (low == high)
	{
		printf("%s", s);
	}
	else
	{
		for (i = low; i <= high; i++)
		{
			swap(s, low, i);
			combine(s, low + 1, high);
			swap(s, low, i);
		}
	}
}

int main(int argc, char **argv)
{
	char *s = "aabccde";

	combine(s, 0, 6);

	return 0;
}
