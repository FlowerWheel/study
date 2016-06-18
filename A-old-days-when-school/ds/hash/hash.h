#ifndef _HASH_H_
#define _HASH_H_

typedef unsigned int Index;

Index Hash1(const char *key, int TableSize);
Index Hash2(const char *key, int TableSize);
Index Hash3(const char *key, int TableSize);

struct ListNode;
typedef struct ListNode *position, *List;
struct HashTbl;
typedef struct HashTbl *HashTable;

#define MINTABLESIZE  11
typedef int	ElemType;

HashTable InitTable(int TableSize);
void DestoryTable(HashTable *ht);
void TraverseTable(HashTable ht);
void Insert(HashTable ht, ElemType key);
position Find(HashTable ht, ElemType key);
void Retrieve(position p);

#endif /*_HASH_H_*/

struct ListNode{
	ElemType		data;
	struct ListNode *next;
};

struct HashTbl{
	int		TableSize;
	List	*TheLists;
};
