#ifndef _BINQUEUE_H_
#define _BINQUEUE_H_

typedef int Elemtype;
typedef struct BinNode *Position, *BinTree;
typedef struct Collection *BinQueue;

void InitBQ(BinQueue *BQ, int MaxSize);
void DestoryBQ(BinQueue *BQ);

int	 IsEmptyBQ(BinQueue BQ);
int	 IsFullBQ(BinQueue BQ);

BinQueue MergeBQ(BinQueue H1, BinQueue H2);

void InsertBQ(Elemtype key, BinQueue BQ);
Position FindBQ(Elemtype key, BinQueue BQ);
Elemtype DeleteMinBQ(BinQueue BQ);
void ClearBQ(BinQueue BQ);

#endif /*_BINQUEUE_H_*/


struct BinNode {
	Elemtype	Data;
	Position	LeftChild;
	Position	NextSibling;
};

struct Collection {
	int CurrentSize;
	int	Capacity;
	BinTree *TheTrees;
};
