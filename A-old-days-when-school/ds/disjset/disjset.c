#include "disjset.h"

void Initilialize(DisjSet S)
{
	int i;

	for (i = NUMSETS; i > 0; --i)
		S[i] = 0;
}
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
//	S[Root2] = Root1;
	
	if ( S[Root2] < S[Root1])
		S[Root1] = Root2;
	else 
	{
		if ( S[Root1] == S[Root2] )
			S[Root1] --;
		S[Root2] = Root1;
	}
}
SetType SetFind(DisjSet S, ElemType X)
{
	if ( S[X] <= 0 )
		return X;
	else 
		return SetFind(S, X);
}


