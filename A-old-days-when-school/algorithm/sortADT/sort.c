#include	"sort.h"
#include	<stdlib.h>
#include	<string.h>


int	InsertSort(void *data, int size, int esize, compare *cmpf)
{
	char	*base = data;
	void	*key;
	int		i, j;

	if ((key = (char *)malloc(esize)) == NULL)
		return -1;

	for (j = 1; j < size; ++j)
	{
		memcpy(key, &base[j * esize], esize);
		i = j - 1;

		while (i >= 0 && cmpf(&base[i * esize], key) > 0)
		{
			memcpy(&base[(i + 1) * esize], &base[i *esize], esize); 
			--i;
		}
		memcpy(&base[(i + 1) * esize], key, esize);
	}
	free(key);
	return 0;
}

static int compare_int(const void *int1, const void *int2)
{
	if (*(const int *)int1 > *(const int *)int2)
		return 1;
	else if (*(const int *)int1 < *(const int *)int2)
		return -1;
	else 
		return 0;
}

static int partition(void *data, int esize, int i, int k, compare cmpf)
{
	char	*a = data;
	void	*pval, *temp;
	int		r[3];

	if ((pval = malloc(esize)) == NULL)
		return -1;

	if ((temp = malloc(esize)) == NULL)
	{
		free(pval);
		return -1;
	}

	r[0] = (rand() % (k - i + 1)) + i;
	r[1] = (rand() % (k - i + 1)) + i;
	r[2] = (rand() % (k - i + 1)) + i;

	InsertSort(r, 3, sizeof(int), compare_int);
	memcpy(pval, &a[r[1] * esize], esize);

	--i; ++k;

	while (1)
	{
		do
		{
			--k;
		} while (cmpf(&a[k * esize], pval) > 0);
		
		do
			++i;
		while (cmpf(&a[i * esize], pval) < 0);

		if (i >= k)
			break;
		else
		{
			memcpy(temp, &a[i * esize], esize);
			memcpy(&a[i * esize], &a[k * esize], esize);
			memcpy(&a[k * esize], temp, esize);
		}
	}
	free(pval);
	free(temp);
	return k;
}

int QuickSort(void *data, int size, int esize, int i, int k, compare *cmpf)
{
	int		j;

	while (i < k)
	{
		if ((j = partition(data, esize, i, k, cmpf)) < 0)
			return -1;
		if (QuickSort(data, size, esize, i, j, cmpf) < 0)
			return -1;
		i = j + 1;
	}
	return 0;
}

static int merge(void *data, int esize, int i, int j, int k, compare *cmpf)
{
	char	*m, *a = data;
	int		ipos = i, jpos = j + 1, mpos = 0;

	if ((m = (char *)malloc(esize * (k - i + 1))) == NULL)
		return -1;
	while (ipos <= j || jpos <= k)
	{
		if (ipos > j)
		{
			while (jpos <= k)
			{
				memcpy(&m[mpos * esize], &a[jpos * esize], esize);
				++jpos;
				++mpos;
			}
			continue;
		} 
		else if (jpos > k) 
		{
			while (ipos <= j)
			{
				memcpy(&m[mpos * esize], &a[ipos * esize], esize);
				++ipos;
				++mpos;
			}
			continue;
		}

		if (cmpf(&a[ipos * esize], &a[jpos * esize]) < 0)	
		{
			memcpy(&m[mpos * esize], &a[ipos * esize], esize);
			++ipos;
			++mpos;
		}
		else 
		{
			memcpy(&m[mpos * esize], &a[jpos * esize], esize);
			++jpos;
			++mpos;
		}
	}

	memcpy(&a[i * esize], m, esize * (k - i + 1));
	free(m);
	return 0;
}

int MergeSort(void *data, int size, int esize, int i, int k, compare *cmpf)
{
	int		j;
	if (i < k)
	{
		j = (int)(( i + k - 1 ) / 2);
		if (MergeSort(data, size, esize, i, j, cmpf) < 0)
			return -1;
		if (MergeSort(data, size, esize, j + 1, k, cmpf) < 0)
			return -1;
		if (merge(data, esize, i, j, k, cmpf) < 0)
			return -1;
	}
	return 0;
}
