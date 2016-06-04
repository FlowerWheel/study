#include	"search.h"
#include	<stdlib.h>
#include	<string.h>

int BinSearch(void *sorted, int size, void *target, int esize, compare *cmpf)
{
	int		l = 0, m, r = size - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		switch(cmpf((char *)sorted + (esize * m), target))
		{	
			case -1:
				l = m + 1;
				break;
			case 1:
				r = m - 1;
				break;
			case 0:
				return m;
		}
	}
	return -1;
}
