#ifndef _ADJGRAPH_
#define _ADJGRAPH_

#include "AdjWGraph.hpp"

class AdjGraph:public AdjWGraph<int>{
	public:
		AdjGraph(int Vertices = 10)
			:AdjWGraph<int>(Vertices, 0){ }
		AdjGraph& Add(const int i, const int j)
		{
			AdjWGraph<int>::Add(i, j, 1);
			return *this;
		}
		AdjGraph& Del(const int i, const int j)
		{
			AdjWGraph<int>::Del(i, j);
			return *this;
		}
};

#endif /*_ADJGRAPH_*/
