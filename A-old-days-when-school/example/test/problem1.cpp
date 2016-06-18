#include <iostream>
using namespace std;

#define M 4
#define N 10

typedef struct tagTag{
	int x, y; //pos
	int dir; // 0 表示横向，1表示纵向
	struct tagTag* pNext;
}Tag, *pTag;

void print(char(*Mtx)[N], int row, int col);
int check(char(*Mtx)[N], int row, int col);
void down(char(*Mtx)[N], int row, int col);

int main(void)
{
	int count;
	int m, n;
	char Mtx[M][N];
	int i, j;
	cin>>count;
	while (count--)
	{
		cin>>m>>n;
		for (i=0; i<m; ++i)
			for (j=0; j<n; ++j)
				cin>>Mtx[i][j];
		while (check(Mtx, i, j)){
			down(Mtx, m, n);
			print(Mtx, m, n);
		}
	}
	return 0;
}

void print(char(*Mtx)[N], int row, int col)
{
	for (int i=0; i<row; ++i)
	{
		for(int j=0; j<col; ++j)
			cout<<Mtx[i][j];
		cout<<endl;
	}
}

void down(char(*Mtx)[N], int row, int col)
{
	for (int i=0; i<col; ++i)
	{
		for(int j=row-1, k=row-1; k>=0; --k)
		{
			while (k>=0 && Mtx[k][i] == '0')
				--k;
			if (k>=0)
			{
				Mtx[j][i] = Mtx[k][i];
				if (j-- !=k)
					Mtx[k][i] = '0';
			}
		}
	}
}

int check(char(*Mtx)[N], int row, int col)
{
	int x, y;
	pTag head = NULL;
	pTag pSave = NULL;
	for (int i=0; i<row; ++i)
		for (int j=0; j<col; ++j)
			if (Mtx[i][j] != '0' && Mtx[i][j] == Mtx[i][j+1] && Mtx[i][j] == Mtx[i][j+2])
			{
				pSave = new	Tag; 
				pSave->x = i;
				pSave->y = j;
				pSave->dir = 0;
				pSave->pNext = head;
				head = pSave;
			}
	for (int j=0; j<col; ++j)
		for (int i=0; i<row-2; ++i)
			if (Mtx[i][j] != '0' && Mtx[i][j] == Mtx[i+1][j] && Mtx[i][j] == Mtx[i+2][j])
			{
				pSave = new	Tag; 
				pSave->x = i;
				pSave->y = j;
				pSave->dir = 1;
				pSave->pNext = head;
				head = pSave;
			}
	if (head == NULL)
		return 0;
	while (head != NULL){
		pSave = head->pNext;
		x = head->x;
		y = head->y;
		if (head->dir)
		{
			Mtx[x][y] = '0';
			Mtx[x+1][y] = '0';
			Mtx[x+2][y] = '0';
		}else{
			Mtx[x][y] = '0';
			Mtx[x][y+1] = '0';
			Mtx[x][y+2] = '0';
		}
		delete head;
		head = pSave;
	}
	return 1;
}
