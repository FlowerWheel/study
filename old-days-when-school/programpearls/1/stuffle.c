#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define		N		10000000

static void stuffle(int *array, int n); /* stuffle the array*/
static void writefile(char *pathname, void *buf, int n); /*  write buf to "pathname" file*/

int main (int argc, char **argv)
{
	int		i, j;
	int		tmp;
	int		*data;
	
	if ((data = malloc ( N * sizeof (int))) == NULL)
		perror("malloc error for data");
	for (i = 0; i < N; i++)
		data[i] = i;
	stuffle(data, N);
	writefile(argv[1], data, N);	
	return 0;
}

static void stuffle(int *array, int n)
{
	int		i, j, tmp;
	srand(time(NULL));
	for(i = 0; i < n; i++){
		j = rand() % N;
		tmp = array[j]; array[j] = array[i]; array[i] = tmp;
	}
}

static void writefile(char *pathname, void *buf, int n)
{
	FILE	*fp;
	if ((fp = fopen(pathname, "r+")) == NULL)
		perror("fopen error");
	if (fwrite(buf,  n * sizeof(buf), 1, fp) != 1)
		perror("write error");
	fclose(fp);
}
