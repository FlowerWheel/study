#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
	ATGraph		atg;

	InitATGraph(&atg, 5);

	CreateATGraph(&atg, 5);

	return 0;
}
