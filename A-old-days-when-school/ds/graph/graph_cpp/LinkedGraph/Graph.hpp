#ifndef  GRAPH_HPP
#define  GRAPH_HPP

#include   "DGraph.hpp"

class Graph:public DGraph{
	public:
		Graph(int Vertices = 10)
			:DGraph(Vertices){}
		Graph& Add(const int i, const int j);
		Graph& Del(const int i, const int j);
		int Degree(int i) const {return InDegree(i);}
		int OutDegree(int i) const {return InDegree(i);}
	protected:
		Graph& AddNoCheck(int i, int j);
};

Graph& Graph::Add(const int i,const int j)
{
	if( i < 1 || i > n || j < 1 || j > n || i == j || Exist(i, j) )
		/* throw BadInput(); */
		;
	return AddNoCheck(i, j);
}

Graph& Graph::AddNoCheck(const int i, const int j)
{
	DGraph::AddNoCheck(i, j);
	DGraph::AddNoCheck(j, i);
	return *this;
}

Graph& Graph::Del(const int i, const int j)
{
	DGraph::Del(i, j);
	DGraph::Del(j, i);
	e++;
	return *this;
}


#endif  /*GRAPH_HPP*/
