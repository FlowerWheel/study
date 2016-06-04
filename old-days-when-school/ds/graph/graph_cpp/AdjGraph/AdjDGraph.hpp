#ifndef _ADJDGRAPH_HPP_
#define _ADJDGRAPH_HPP_

#include "AdjWDGraph.hpp"

class AdjDGraph:public AdjWDGraph<int>{
	public:
		AdjDGraph(int Vertices = 10) 
			:AdjWDGraph<int>(Vertices, 0)
	   	{ }
		/* ~AdjDGraph() { AdjWDGraph<int>::~AdjWDGraph() } */
		AdjDGraph& Add(const int i, const int j)
		{
			AdjWDGraph<int>::Add(i, j, 1);
			return *this;
		}
		AdjDGraph& Del(const int i, const int j)
		{
			AdjWDGraph<int>::Del(i, j);
			return *this;
		}
	private:
};

#endif /*_ADJDGRAPH_HPP_*/
