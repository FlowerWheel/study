#ifndef  RANDOM_H
#define  RANDOM_H


#define		A	48271L
#define		M	2147483647L

#define		Q	( M / A )
#define		R	( M % A )

//static	unsigned long Seed = 1;

void Srand(const unsigned long seed);

double Random1(void);

double Random2(void);


#endif  /*RANDOM_H*/
