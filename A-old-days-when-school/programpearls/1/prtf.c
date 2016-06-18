#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main ( int argc, char *argv[] )
{
	FILE	*fp;
	int		*data;
	int		i;

	data = malloc (10000000 * sizeof (int));
	if ((fp = fopen(argv[1],"r")) == NULL)
		perror("fopen error!");
	if (fread(data, 10000000 * sizeof(int), 1, fp) != 1)
		perror("fwrite error!");
	for (i = 0; i < 10000000; i++)
		printf("%d\t", data[i]);
	fclose(fp);
	return 0;
}
