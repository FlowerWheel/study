#include "cclklist.h"
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
	head->Prev = head;
	head->Next = head;
	return head;
}

int	 IsEmpty (const List L)
{
	return L->Next == L;
}

int  Length (const List L)
{
	int			len = 0;
	PtrToNode	cur;
	if (IsEmpty(L))
		return 0;
	cur = L->Next;
	while (cur != L){
		cur = cur->Next;
		len++;
	}
	return len;
}

int  Insert (const int i, const ElemType e, List L)
{
	PtrToNode		lnode, mnode, rnode;	
	if ((mnode = malloc (sizeof (struct Node))) == NULL)
		err_sys("malloc error");
	mnode->Elem = e;
	if ((lnode = LocatePrevious (i, L)) == NULL)
		return 0;
	rnode = lnode->Next;
	lnode->Next = mnode;
	mnode->Prev = lnode;
	rnode->Prev = mnode;
	mnode->Next = rnode;
	return 1;
}

Position Locate (int i, const List L)
{
	PtrToNode	cur = LocatePrevious(i, L);
	return  (cur == NULL || cur->Next == NULL) ? NULL : cur->Next;
}

Position LocatePrevious (int i, const List L)
{
	PtrToNode	cur = L;
	while (--i && cur->Next != L)
		cur = cur->Next;
	if (i > 0)
		return NULL;
	return cur;	
}

int  FindIndex (const ElemType e, const List L)
{
	int			i = 1;
	PtrToNode	cur;
	cur = L->Next;
	while(cur != L && cur->Elem != e){
		cur = cur->Next;
		i++;
	}
	if (cur == L)	
		return -1;
	return i;
}

Position Find (const ElemType e,const List L)
{
	PtrToNode	cur = FindPrevious(e, L);
	return cur ? NULL : cur->Next;
}

Position FindPrevious (const ElemType e,const List L)
{
	PtrToNode	cur = L;
	while (cur->Next != L){
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
	while (cur != L){
		func(cur->Elem);
		cur = cur->Next;
	}
	printf("\n");
}
void Delete (const ElemType e, List *L)
{
	PtrToNode		lnode, mnode, rnode;	
	if((lnode = FindPrevious (e, *L)) == NULL)
		err_quit("Delete error: can not find element");
	mnode = lnode->Next;
	rnode = mnode->Next;
	lnode->Next = rnode;
	rnode->Prev = lnode;
	free(mnode);
}

void Deletei (const int i, List *L)
{
	PtrToNode		lnode, mnode, rnode;	
	if((lnode = LocatePrevious (i, *L)) == NULL)
		err_quit("Delete error: can not locate position");
	mnode = lnode->Next;
	rnode = mnode->Next;
	lnode->Next = rnode;
  	rnode->Prev = lnode;
	free(mnode);
}

void DeleteList (List *L)
{
	PtrToNode	cur, del;
	cur = (*L)->Next;
	(*L)->Next = NULL;
	while (cur){
		del = cur;
		free(del);
		cur = cur->Next;
	}
}
