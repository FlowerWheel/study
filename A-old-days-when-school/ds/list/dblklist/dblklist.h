#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "lueap.h"

typedef int		ElemType;
typedef struct  Node{
	ElemType	Elem;
	struct Node *Prev;
	struct Node	*Next;
}DblkNode, *PtrToNode;

typedef PtrToNode	List;
typedef PtrToNode	LinkedList;
typedef PtrToNode	Position;

List CreatList (void);

int	 IsEmpty (const List L);
int  Length (const List L);

void Insert (const ElemType e, const int i, List L);

Position Locate (int i, const List L);
Position LocatePrevious (int i, const List L);

int		 FindIndex (const ElemType e, const List L);

Position Find (const ElemType e, const List L);
Position FindPrevious (const ElemType e, const List L);

void Traverse(List L,void (*func) (ElemType));

void Delete (const ElemType e, List *L);
void Deletei (const int i, List *L);
void DeleteList (List *L);

#endif /*_LINKEDLIST_H_*/
