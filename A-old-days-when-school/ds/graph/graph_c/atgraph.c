#include "graph.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void InitATGraph(ATGraph *G, int vcount)
{
	int		i;
	if (((*G) = malloc(vcount * sizeof(struct ATVertex))) == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < vcount; i++)
	{
		(*G)[i].vnum = 0;
		(*G)[i].Next = NULL;
	}
}
void CreateATGraph(ATGraph *G, int vcount)
{
	int		i, vnum;
	int		k;
	PtrToATV	neww, cur;

	for (i = 0; i < vcount; i++)
	{
		cur = &(*G)[i];
		k = 0;
		while (k < vcount)
		{
			scanf("%d", &vnum);
			if (vnum > 0 && vnum <= vcount)
			{

				if ((neww = malloc(sizeof(struct ATVertex))) == NULL)
				{
					perror("malloc error");
					exit(EXIT_FAILURE);
				}
				neww->vnum = vnum;
				neww->Next = NULL;
				cur->Next = neww;
				cur = cur->Next;
				(*G)[i].vnum++;
				k++;
			}
			else if (vnum == 0)	
				break;
			else
				printf("please input a num between 0 ~ %d\n", vcount);
		}
		if (i + 1 < vcount)
			printf("printf next w to v = %d\n", i + 1);		
	}
}
void TopSortATG(const ATGraph G)
{

}
