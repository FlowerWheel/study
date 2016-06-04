#include	"random.h"

static	unsigned long Seed = 1;

void Srand(const unsigned long seed)
{
	Seed = seed;
}

double Random1(void)
{
	Seed = (A * Seed) % M;
	return (double) Seed / M;
}

double Random2(void)
{
	long	TmpSeed;

	TmpSeed = A * (Seed % Q) - R * (Seed / Q);
	if (TmpSeed >= 0)
		Seed = TmpSeed;
	else 
		Seed = TmpSeed + M;
	return (double) Seed / M;
}
