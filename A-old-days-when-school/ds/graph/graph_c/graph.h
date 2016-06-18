#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef  int  GElemType;
typedef struct ATVertex{
	GElemType		Elem;
	int			    vnum;	
	struct ATVertex	*Next;
}ATVertex, *PtrToATV, *ATGraph;

void InitATGraph(ATGraph *G, int vcount);
void CreateATGraph(ATGraph *G, int vcount);
void TopSortATG(const ATGraph G);

#endif
