#include "polynomaial.h"
#include <string.h>
#include <unistd.h>

void ZeroPolynomaial(polynomaial Poly)
{
//	int		i;
//	for(i = 0; i < MaxDegree; i++)
//		Poly->CoeffArray[i] = 0;
	memset(Poly->CoeffArray, 0, MaxDegree);
//	wmemset();
//	swab();
//	bzero(Poly->CoeffArray, MaxDegree + 1);
	Poly->HighPower = 0;
}

void AddSubPolynomaial(polynomaial Poly1, polynomaial Poly2, polynomaial sum, int type)
{
	int		i, maxHighPower;
	ZeroPolynomaial(sum);
	maxHighPower = Max(Poly1->HighPower, Poly2->HighPower);
	if (type == ADD){
		for(i = 0; i < maxHighPower; i++)
			sum->CoeffArray[i] = Poly1->CoeffArray[i] + Poly2->CoeffArray[i];
	}
	else if (type == SUB){
		for(i = 0; i < maxHighPower; i++)
			sum->CoeffArray[i] = Poly1->CoeffArray[i] - Poly2->CoeffArray[i];
	}
	else 
		;
}
void MultPolynomaial( polynomaial Poly1, polynomaial Poly2, polynomaial mult)
{
	int		i, j;
	ZeroPolynomaial(mult);
	mult->HighPower = Add(Poly1->HighPower, Poly2->HighPower);
	if (mult->HighPower > MaxDegree)
		err_quit("Exceeded array size");
	for(i = 0; i < Poly1->HighPower; i++)
		for(j = 0; j < Poly2->HighPower; j++)
			mult->CoeffArray[i+j] = Poly1->CoeffArray[i] * Poly2->CoeffArray[j];
}
