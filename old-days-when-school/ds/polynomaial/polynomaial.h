#ifndef  POLYNOMAIAL_H
#define  POLYNOMAIAL_H

#include "lueap.h"
#include <string.h>

#define		MaxDegree		256

#define		Add(a, b)   (a) + (b);

#define		ADD				1
#define		SUB				0

#define		AddPolynomaial(Poly1, Poly2, sum) AddSubPolynomaial(Poly1, Poly2, sum, ADD)
#define		SubPolynomaial(Poly1, Poly2, sum) AddSubPolynomaial(Poly1, Poly2, sum, SUB)

typedef struct {
	int		CoeffArray[MaxDegree+1];
	int		HighPower;
}*polynomaial;

void ZeroPolynomaial(polynomaial Poly);
void AddSubPolynomaial(polynomaial Poly1, polynomaial Poly2, polynomaial sum, int type);
void MultPolynomaial( polynomaial Poly1, polynomaial Poly2, polynomaial mult);

#endif  /*POLYNOMAIAL_H*/
