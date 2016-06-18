#include "binqueue.h"

void InitBQ(BinQueue *BQ, int MaxSize)
{
	int		i;
	if ((*BQ = malloc (sizeof (BinNode))) == NULL)
		err_sys("InitBQ malloc error for *BQ");
	if ((*BQ)->TheTrees = malloc (MaxSize * sizeof (Position)) == NULL)
		err_sys("InitBQ malloc error for (*BQ)->TheTrees");
	(*BQ)->CurrentSize = 0;
	(*BQ)->Capacity = MaxSize;
	for (i = 0; i < MaxSize; ++i)
		(*BQ)->TheTrees[i] = NULL;
}

static void DestoryBinTree(BinTree *BT)
{
	if (*BT != NULL)
	{
		DestoryBinTree(&(*BT)->LeftChild);
		DestoryBinTree(&(*BT)->firstsibling);
		free(*BT);
		*BT = NULL;
	}
}

void DestoryBQ(BinQueue *BQ)
{
	if (*BQ == NULL)
		;
	else if (IsEmptyBQ(*BQ))
	{
		free(TheTrees);
		(*BQ)->TheTrees = NULL;
	}
	else 
	{
		for (i = 0; i < (*BQ)->CurrentSize, ++i)
			if ((*BQ)->TheTrees[i] != NULL)
				DestoryBinTree(&(*BQ)->TheTrees[i]);
		free(TheTrees);
		(*BQ)->TheTrees = NULL;
	}
}

int	 IsEmptyBQ(BinQueue BQ)
{
	if (BQ != NULL)
		return (BQ->CurrentSize == 0);
	else 
		return -1;
}

int	 IsFullBQ(BinQueue BQ)
{
	if (BQ != NULL)
		return (BQ->CurrentSize == BQ->Capacity);
	else 
		return -1;
}

static BinTree CombineTrees(BinTree T1, BinTree T2)
{
	if (T1->Data > T2->Data)
		return CombineTrees(T2, T1);
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}
BinQueue MergeBQ(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, Carry = NULL;
	int i, j;
	BinQueue	H;
	/*
	BinQueue	H3;
	InitBQ(&H3, H1->Capacity + H2->Capacity);
	*/

	if (H1->CurrentSize < H2->CurrentSize)
	{
		H = H1;
		H1 = H2;
		H2 = H;
	}
	for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
	{
		T1 = H1->TheTrees[i];
		T2 = H2->TheTrees[i];
		switch (!!T1 + 2 * !!T2 + 4 * !!Carry)
		{
			case 0:
			case 1:
				break;

			case 2:
				H1->TheTrees[i] = T2;
				H2->TheTrees[i] = NULL;
				break;

			case 4:
				H1->TheTrees[i] = Carry;
				Carry = NULL;
				break;

			case 3:
				Carry = CombineTrees(T1, T2);
				H1->TheTrees[i] = NULL;
				H2->TheTrees[i] = NULL;
				break;

			case 5:
				Carry = CombineTrees(T1, Carry);
				H1->TheTrees[i] = NULL;
				break;

			case 6:
				Carry = CombineTrees(T2, Carry);
				H2->TheTrees[i] = NULL;
				break;

			case 7:
				H1->TheTrees[i] = Carry;
				Carry = CombineTrees(T1, T2);
				H2->TheTrees[i] = NULL;
				break;
		}
	}

}

void InsertBQ(Elemtype key, BinQueue BQ)
{
	BinQueue	H;

	InitBQ(&H, 2);

	if (H->TheTrees[0] = malloc (sizeof(Position)) == NULL)
		err_sys("InsertBQ malloc error");

	H->TheTrees[0]->Data = key;
	H->TheTrees[0]->LeftChild = NULL;
	H->TheTrees[0]->NextSibling = NULL;

	MergeBQ(BQ, H);
}
Position FindBQ(Elemtype key, BinQueue BQ);
Elemtype DeleteMinBQ(BinQueue BQ)
{
	int i, j;
	int MinTree;
	BinQueue DeletedQueue;
	Position DeletedTree, OldRoot;
	Elemtype MinItem;
	Elemtype Infinity = -1;

	if ( IsEmptyBQ(BQ) )
	{
		err_msg("A empty BQ");
		return Infinity;
	}

	MinItem = Infinity;
	
	for (i = 0; i < BQ->CurrentSize; ++i)
	{
		if (BQ->TheTrees[i] &&
				BQ->TheTrees[i]->Data < MinItem)
		{
			MinItem = BQ->TheTrees[i]->Data;
			MinTree = i;
		}
	}

	DeletedTree = BQ->TheTrees[MinTree];
	OldRoot = DeletedTree;
	DeletedTree = DeletedTree->LeftChild;
	free(OldRoot);

	InitBQ(&DeletedQueue, 1 << MinTree);

	for (j = MinTree; j >= 0; --j)
	{
		DeletedQueue->TheTrees[j] = DeletedTree;
		DeletedTree = DeletedTree->NextSibling;
		DeletedQueue->TheTrees[j]->NextSibling = NULL;
	}

	BQ->TheTrees[MinTree] = NULL;
	BQ->CurrentSize -= DeletedQueue->CurrentSize + 1;
	
	MergeBQ(H, DeletedQueue);
	return MinItem;
}
void ClearBQ(BinQueue BQ)
{
	if (BQ == NULL)
		;
	else if (IsEmptyBQ(BQ))
		;
	else 
	{
		for (i = 0; i < (*BQ)->CurrentSize, ++i)
			if ((*BQ)->TheTrees[i] != NULL)
				DestoryBinTree(&(*BQ)->TheTrees[i]);
	}
}
