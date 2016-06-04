#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define		N	250000

static void bubblesort(int *array, int n);

int main (int argc, char **argv)
{
	int		i, n, cur, j;
	int		lift, right;
	int		data;
	int		*buf;	
	int		fd;
	FILE	*fp, *fp_t;

	if ((fp = fopen(argv[1], "r")) == NULL)
		perror("fopen error for argv[1]");
	if ((fd = open("tempfile", O_RDWR|O_CREAT)) == -1)
		perror("open error for tempfile");
	if ((fp_t = fdopen(fd, "r+")) == NULL)
		perror("fdopen error");

	if ((buf = malloc (N * sizeof(int))) == NULL)
		perror("malloc error");

	for (i = 1; i <= 40; i++){
		lift = (i-1) * N; right = i * N - 1; cur = 0;
		while ( (n = fread(&data, sizeof(int), 1, fp)) > 0){
			if (data > lift && data < right){
				buf[cur] = data;
				cur++;
			}
			bubblesort(buf, cur);
			
			for (j = 0; j < cur; j++)
				printf("buf[j] = %d \t", buf[j]);

			if ((n = fwrite(buf, cur * sizeof(int), 1, fp_t)) != 1)
			//	perror("fwrite error");
			fseek(fp, 0, SEEK_SET);	
			bzero(buf, N);
		}
		fclose(fp);
		fclose(fp_t);
		close(fd);
		
		unlink(argv[1]);
		rename("tempfile", argv[1]);
	}
	return 0;
}
static void bubblesort(int *array, int n)
{
	int		i, j, tmp;
	for (i = 0; i < n; i++)
		for (j = 0; j < n-i; j++)
			if(array[j] > array[j+1]){
				tmp = array[j];	array[j+1] = array[j]; array[j] = tmp;
			}
}
