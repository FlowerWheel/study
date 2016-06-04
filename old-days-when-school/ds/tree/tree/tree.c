#include "lueap.h"

typedef char DataType;
typedef struct CSNode
{
	struct CSNode *firstchild,*nextsibling;
	DataType data;
}CSNode,*CSTree;

void InitCSTree(CSTree *T)
{
	*T=0;
}
void DestroyCSTree(CSTree *T)
{
	CSTree p=*T;
	if(p)
	{
		DestroyCSTree(&(p->firstchild));
		DestroyCSTree(&(p->nextsibling));
		free(p);
		*T = 0;
	}
}
void CreateCSTree(CSTree *T,char *e,int *index)
{
	if(e[*index]=='0')
	{
		*T=0;
		(*index)++;
	}
	else
	{
		*T = malloc (sizeof(CSNode));
		(*T)->data=e[*index];
		(*index)++;
		CreateCSTree(&((*T)->firstchild),e,index);
		CreateCSTree(&((*T)->nextsibling),e,index);
	}
}
int DepCSTree(CSTree T)
{
	CSNode *p;
	int k,d=0;
	if(T==NULL)
		return 0;
	p=T->firstchild;
	while(p!=NULL)
	{
		k=DepCSTree(p);
		if(d<k)
			d=k;
		p=p->nextsibling;
	}
	return d+1;
}
void PreTraverseCSTree(CSTree T,void(*visit)(DataType *e))
{
	if(T)
	{
		(*visit)(&T->data);
		PreTraverseCSTree(T->firstchild,visit);
		PreTraverseCSTree(T->nextsibling,visit);
	}
}
void PostTraverseCSTree(CSTree T,void(*visit)(DataType *e))
{
	if(T)
	{
		PostTraverseCSTree(T->firstchild,visit);
		(*visit)(&T->data);
		PostTraverseCSTree(T->nextsibling,visit);
	}
}
void DisplayCSTree(DataType *e)
{
	printf("%c\t", *e);
}

int main()
{
	char	*test;
	test = "ABE0FH0I0J000C0DG00000";
//	test = "AB0C0DH00EI0JP0Q000FK0L0M00G0N0";
	int h=0;
	CSTree T;
	InitCSTree(&T);
	CreateCSTree(&T,test,&h);
	printf("树的先根遍历结果是\n");
	PreTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("树的后根遍历结果是\n");
	PostTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("树的深度是:%d\n", DepCSTree(T));
	DestroyCSTree(&T);
	return 0;
}
