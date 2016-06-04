#include "hash.h"
#include "lueap.h"
#include "bitmap.h"

Index Hash1(const char *key, int TableSize)
{
	//如果TableSize很大，那么此函数不能很好的分配关键字
	//分配不均匀
	unsigned int	HashVal = 0;
	while (*key != '\0')
		HashVal += *key++;
	return HashVal % TableSize;
}
Index Hash2(const char *key, int TableSize)
{
	//3个字母的组合实际上左右2851种左右，显然不太合理
	return (key[0] + 27 * key[1] + 729 * key[2]);
}
Index Hash3(const char *key, int TableSize)
{
	unsigned int	HashVal = 0;
	while (*key != '\0')
		HashVal = (HashVal << 5) + *key++;
	return HashVal % TableSize;
}



static int NextPrime(int size)
{
	int		i;
	int		bmsize = 2 * size;

	if (bmsize > 282)
		bmsize = 282;

	BitMap bm = MakePrimeTable(bmsize);
	
	for (i = size; i < bmsize; i++)
		if (GetBitBM(&bm, i))
			break;
	return i;
}
HashTable InitTable(int TableSize)
{
	HashTable	T;
	int			i;

	if (TableSize < MINTABLESIZE)
		err_msg("TableSize is too small");

	if ((T = malloc(sizeof(struct HashTbl))) == NULL)
		err_sys("malloc error");

	T->TableSize = NextPrime(TableSize);
	if ((T->TheLists = malloc((T->TableSize) * sizeof(List))) == NULL)
		err_sys("malloc error");

	for (i = 0; i < T->TableSize; i++)
	{
		T->TheLists[i] = malloc(sizeof(struct ListNode));
		if (T->TheLists[i] == NULL)
			err_sys("malloc error");
		else 
			T->TheLists[i]->next = NULL;
	}
	return T;
}
void DestoryTable(HashTable *ht)
{
	int			i;
	position	p, pnext;
	
	if (*ht == NULL)
		err_msg("a empty tree");
	else
	{
		if ((*ht)->TheLists != NULL)
		{
			for (i = 0; i < (*ht)->TableSize; i++)
			{
				p = (*ht)->TheLists[i];
				pnext = p->next;
				while (pnext)
				{
					free(p);
					p = pnext;
					pnext = p->next;
				}
			}
			free(*ht);
			*ht = NULL;
		}
	}
}
void TraverseTable(HashTable ht)
{
	int			i;
	position	p, pnext;

	if (ht->TheLists != NULL)
	{
		for (i = 0; i < ht->TableSize; i++)
		{
			p = ht->TheLists[i];
			pnext = p->next;
			printf("Table[%d] : {", i);
			while (pnext)
			{
				printf("[%d]", pnext->data);
				p = pnext;
				pnext = p->next;
			}
			printf("}\n");
		}
	}
}
/*
static Index Hash(int size, ElemType key)
{
	return key % size;
}
*/
#define Hash(size, key) (key % size)
position Find(HashTable ht, ElemType key)
{
	position	p;
	
	p = ht->TheLists[Hash(ht->TableSize, key)];
	p = p->next;
	while (p != NULL)
	{
		if (p->data == key)
			break;
		p = p->next;
	}
	return p;
}
void	Insert(HashTable ht, ElemType key)
{
	position	NewCell;
	List		L;

	L = ht->TheLists[Hash(ht->TableSize, key)];
	
	if ((NewCell = malloc(sizeof(struct ListNode))) == NULL)
		err_sys("malloc error");
	else 
	{
		NewCell->next = L->next;
		NewCell->data = key;
		L->next = NewCell;
	}
}
void Retrieve(position p)
{
	if (p == NULL)
		err_msg("p == NULL");
	else 
		printf("%d ", p->data);
}
