#ifndef _TABLE_H_
#define _TABLE_H_

#include    "lueap.h"

typedef int ElemType;
typedef struct ElementType{
	int		key;
}ElementType;

typedef struct Node{
	struct Node		*prev;
	struct Node		*next;
	ElemType		elem;
}Node, *PtrToNode, *Position, *doubleLinkedList;

typedef struct IndexNode{
	doubleLinkedList	head;
	doubleLinkedList	tail;
}*PtrToIndexNode, *Table, *List, *DBList, *Stack, *Queue;

//The Conmon Interface For List Stack Queue;
void creat (Table *T);
void Creat (Table *T, void (*input)(ElemType *e));
void Init (Table *T);
void Initialization (Table *T);
int	 IsEmpty (const Table T);
void MakeEmpty(const Table T);
void Clear(const Table T);
void Destory(Table *T);

//The Special Interface For List;
int  Length(const Table T);
int  Insert_i(const Table T, const int i, const ElemType e);
int  Insert_p(const Table T, const Position p, const ElemType e);
int  Delete_i(const Table T, const int i, const ElemType e);
int  Delete_p(const Table T, const Position p, const ElemType e);
Position Find(const Table T, const ElemType e);
Position Locate(const Table T, int i);
void Traverse(const Table T,void (*handle)(PtrToNode node));

//The Special Interface For Stack And Queue
//Stack:puch pop top; Queue:Enqueue Dequeue front;
void  Puch_h(Table T, const ElemType e);
void  Puch_t(Table T, const ElemType e);
void  Pop_h (Table T);
void  Pop_t (Table T);
ElemType  Top_h (Table T);
ElemType  Top_t (Table T);
ElemType  TopPop_h (Table T);
ElemType  TopPop_t (Table T);

#endif
