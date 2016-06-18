#include "dblklist.h"
#include <stdlib.h>

static void print (ElemType e)
{
	printf("%d\t", e);
}

List CreatList (void)
{
	DblkNode		*head;
	if ((head = malloc (sizeof(DblkNode))) == NULL)
		err_quit("malloc error");
	head->Prev = NULL;
	head->Next = NULL;
	return head;
}

int	 IsEmpty (const List L)
{
	return L->Next == NULL;
}

int  Length (const List L)
{
	int			len = 0;
	PtrToNode	cur = L->Next;
	while (cur){
		cur = cur->Next;
		len++;
	}
	return len;
}

void Insert (const ElemType e, const int i, List L)
{
	PtrToNode		lnode, mnode, rnode;	
	lnode = LocatePrevious (i, L);
	rnode = lnode->Next;
	if ((mnode = malloc (sizeof (struct Node))) == NULL)
		err_sys("malloc error");
	mnode->Elem = e;
	lnode->Next = mnode;
	mnode->Prev = lnode;
	if (rnode != NULL)
		rnode->Prev = mnode;
	mnode->Next = rnode;
}

Position Locate (int i, const List L)
{
	PtrToNode	cur = LocatePrevious(i, L);
	return cur->Next;	
}

Position LocatePrevious (int i, const List L)
{
	PtrToNode	cur;
	cur = L;
	while (--i && cur)
		cur = cur->Next;
	if (i > 0)
		err_quit("overflow");
	return cur;	
}

int  FindIndex (const ElemType e, const List L)
{
	int			i = 1;
	PtrToNode	cur;
	cur = L->Next;
	while(cur && cur->Elem != e){
		cur = cur->Next;
		i++;
	}
	if (cur == NULL)	
		return -1;
	return i;
}

Position Find (const ElemType e,const List L)
{
	PtrToNode	cur = FindPrevious(e, L);
	return cur->Next;
}

Position FindPrevious (const ElemType e,const List L)
{
	PtrToNode	cur = L;
	while (cur->Next){
		if (cur->Next->Elem == e)
			return cur;
		cur = cur->Next;
	}
	return NULL;
}

void Traverse(List L,void (*func) (ElemType))
{
	PtrToNode		cur = L->Next;
	if (func == NULL)
		func = print;
	while (cur){
		func(cur->Elem);
		cur = cur->Next;
	}
	printf("\n");
}
void Delete (const ElemType e, List *L)
{
	PtrToNode		lnode, mnode, rnode;	
	lnode = FindPrevious (e, *L);
	mnode = lnode->Next;
	rnode = mnode->Next;
	lnode->Next = rnode;
	if(rnode != NULL)
	   	rnode->Prev = lnode;
	free(mnode);
}

void Deletei (const int i, List *L)
{
	PtrToNode		lnode, mnode, rnode;	
	lnode = LocatePrevious (i, *L);
	mnode = lnode->Next;
	rnode = mnode->Next;
	lnode->Next = rnode;
	if (rnode != NULL)
	   	rnode->Prev = lnode;
	free(mnode);
}

void DeleteList (List *L)
{
	PtrToNode	cur;
	cur = (*L)->Next;
	while (cur){
		free(*L);
		(*L) = cur;
		cur = cur->Next;
	}
}
