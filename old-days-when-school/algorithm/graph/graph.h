#ifndef  GRAPH_H
#define  GRAPH_H

#include	<stdlib.h>
#include	"list.h"
#include	"set.h"


typedef struct _AdjList{
	void	*vertex;
	Set		adjacent;
}AdjList;

typedef struct _Graph{
	int		vcount;
	int		ecount;

	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);

	List	adjlists;
}Graph;


#endif  /*GRAPH_H*/
