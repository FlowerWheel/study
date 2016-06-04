#ifndef _DisjSet_H_
#define _DisjSet_H_

#define NUMSETS 50
typedef int DisjSet[NUMSETS + 1]
typedef int SetType;
typedef int ElemType;

void Initilialize(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType SetFind(DisjSet S, ElemType X);

#endif /*_DisjSet_H_*/
