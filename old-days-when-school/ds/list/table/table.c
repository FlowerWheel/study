#include "table.h"

static void GetElem(ElemType *e)
{
	scanf("%d", &(*e));
}

//The Conmon Interface For List Stack Queue;
void creat (Table *T)
{
	Creat(&(*T), GetElem);
}
void Creat (Table *T, void (*input)(ElemType *e))
{
	int			n, i;
	PtrToNode	add, l, r;
	Init (T);
	printf("please input the number of node you want to creat in the Table:");
	scanf("%d", &n);
	for (i = n; i > 0; i--){
		if ((add = malloc (sizeof (Node))) == NULL)	
			err_sys("malloc error");
		input (&(add->elem));
		r = (*T)->tail;
		l = r->prev;
		add->next = l->next;
		add->prev = r->prev;
		l->next = add;
		r->prev = add;
	}
}
void Init (Table *T)
{
	if (*T == NULL)
		if ((*T = malloc (sizeof (struct IndexNode))) == NULL)
			err_sys("malloc error");
		
	if ((*T)->head == NULL && (*T)->tail == NULL){
		if( ((*T)->head = malloc (sizeof (Node)))== NULL 
			|| ((*T)->tail = malloc (sizeof (Node))) == NULL )	
			err_sys ("malloc error for *T->head and *T->tail");
		(*T)->head->next = (*T)->tail;
		(*T)->head->prev = NULL;
		(*T)->tail->prev = (*T)->head;
		(*T)->tail->next = NULL;
	}
}
void Initialization (Table *T)
{
	Init (T);
}
int	 IsEmpty (const Table T)
{
	return T->head->next == T->tail;
}
void MakeEmpty(const Table T)
{
	while (!IsEmpty(T))
		Pop_h(T);
}
void Clear(const Table T)
{
	while (!IsEmpty(T))
		Pop_h(T);
}
void Destory(Table *T)
{
	MakeEmpty(*T);
	free((*T)->head);
	free((*T)->tail);
	free(*T);
}

//The Special Interface For List;
int  Length(const Table T)
{
	int		len = 0;
	PtrToNode	cur = T->head->next;
	while (cur != T->tail){
		len ++;
		cur = cur->next;
	}
	return len;
}
int  Insert_i(const Table T, const int i, const ElemType e)
{//success return 0, failure return -1
	int		pos = i;
	PtrToNode	add, l, r;
	l = T->head;
	while (--pos && l->next != T->tail)
		l = l->next;
	if (pos != 0){
		fprintf (stderr, "Insert_i: i = %d is overflow\n", i);
		return -1;
	}
	else {
		if ((add = malloc (sizeof (Node))) == NULL)
			err_sys("malloc error");
		r = l->next;
		add->elem = e;
		add->next = l->next;
		add->prev = r->prev;
		l->next = add;
		r->prev = add;
		return 0;
	}
}
int  Insert_p(const Table T, const Position p, const ElemType e)
{//success return 0, failure return -1
	PtrToNode	add, l, r;
	if (p == T->head || p == NULL){
		fprintf (stderr, "Insert_p: insert in a wrong Position\n");
		return -1;
	}
	else {
		if ((add = malloc (sizeof (Node))) == NULL)
			err_sys("malloc error");
		l = p->prev;
		r = p;
		add->elem = e;
		add->next = l->next;
		add->prev = r->prev;
		l->next = add;
		r->prev = add;
		return 0;
	}
}
int  Delete_i(const Table T, const int i, const ElemType e)
{//success return 0, failure return -1
	int		pos = i;
	PtrToNode	del, l, r;
	l = T->head;
	while (--pos && l->next != T->tail){
		l = l->next;
	}
	if (pos != 0){
		fprintf (stderr, "Delete_i: i is overflow\n");
		return -1;
	}
	else {
		del = l->next;
		r = del->next;
		l->next = del->next;
		r->prev = del->prev;
		free (del);
		return 0;
	}
}
int  Delete_p(const Table T, const Position p, const ElemType e)
{//success return 0, failure return -1
	PtrToNode	del, l, r;
	if (p == T->head || p == NULL){
		fprintf (stderr, "Delete_p: Delete with a wrong Position\n");
		return -1;
	}
	else {
		l = p->prev;
		r = p->next;
		del = p;
		l->next = del->next;
		r->prev = del->prev;
		free (del);
		return 0;
	}
}
Position Find(const Table T, const ElemType e)
{//success return pos, failure return NULL
	PtrToNode	pos = T->head->next;
	while (pos != T->tail && pos->elem != e)
		pos = pos->next;
	if (pos == T->tail)
		return NULL;	
	return pos;
}
Position Locate(const Table T, const int i)
{//success return pos, failure return NULL
	int		loc = i;
	PtrToNode	pos = T->head;
	while (--loc &&  pos->next != T->tail)
		 pos = pos->next;
	if (loc != 0){
		fprintf(stderr, "Locate: i is overflow");
		return NULL;
	}
	return pos;
}
void Traverse(const Table T,void (*handle)(PtrToNode node))
{
	PtrToNode		ptn = T->head->next;
	while (ptn != T->tail){
		handle(ptn);
		ptn = ptn->next;
	}
}

//The Special Interface For Stack And Queue
void  Puch_h(Table T, const ElemType e)
{
	PtrToNode	add, l, r;
	if ((add = malloc (sizeof (Node))) == NULL)
		err_sys("malloc error");
	add->elem = e;
	l = T->head;
	r = l->next;
	add->next = l->next;
	add->prev = r->prev;
	l->next = add;
	r->prev = add;
}
void  Puch_t(Table T, const ElemType e)
{
	PtrToNode	add, l, r;
	if ((add = malloc (sizeof (Node))) == NULL)
		err_sys("malloc error");
	add->elem = e;
	l = T->tail->prev;
	r = l->next;
	add->next = l->next;
	add->prev = r->prev;
	l->next = add;
	r->prev = add;
}
void  Pop_h (Table T)
{
	PtrToNode	del, l, r;
	if (IsEmpty (T))
		fprintf(stderr,"pop from a empty table");
	else{
		l = T->head;
		del = l->next;
		r = del->next;
		l->next = del->next;
		r->prev = del->prev;
		free (del);
	}
}
void  Pop_t (Table T)
{
	PtrToNode	del, l, r;
	if (IsEmpty (T))
		fprintf(stderr,"pop from a empty table");
	else{
		l = T->tail->prev->prev;
		del = l->next;
		r = del->next;
		l->next = del->next;
		r->prev = del->prev;
		free (del);
	}
}
ElemType  Top_h (Table T)
{
	if (IsEmpty (T))
		err_ret("pop from a empty table");
	return T->head->next->elem;
}
ElemType  Top_t (Table T)
{
	if (IsEmpty (T))
		err_ret("pop from a empty table");
	return T->tail->prev->elem;
}
ElemType  TopPop_h (Table T)
{
	PtrToNode	del, l, r;
	ElemType	e;
	if (IsEmpty (T))
		err_ret("pop from a empty table");

	l = T->head;
	del = l->next;
	r = del->next;
	l->next = del->next;
	r->prev = del->prev;
	e = del->elem;
	free (del);
	return e;
}
ElemType  TopPop_t (Table T)
{
	PtrToNode	del, l, r;
	ElemType	e;
	if (IsEmpty (T))
		err_ret("pop from a empty table");

	l = T->tail->prev->prev;
	del = l->next;
	r = del->next;
	l->next = del->next;
	r->prev = del->prev;
	e = del->elem;
	free (del);
	return e;
}
