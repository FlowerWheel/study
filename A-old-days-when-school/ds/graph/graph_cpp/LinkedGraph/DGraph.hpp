#ifndef  DGRAPH_HPP
#define  DGRAPH_HPP

#include	<list>
#include	<algorithm>
#include   "GraphBase.hpp"

using std::list;

class DGraph:public GraphBase<int>{
	public:
		DGraph(int Vertices = 10)	
			:GraphBase<int>(Vertices){}

		bool Exist(const int i, const int j) const;
		DGraph& Add(const int i, const int j);
		DGraph& Del(const int i, const int j);
		int InDegree(const int i) const;
	protected:
		DGraph& AddNoCheck(const int i, const int j);
	private:
};

bool DGraph::Exist(int i,int j) const
{
	if( i < 1 || i > n )
		//throw OutOfBounds();
		;
	if ( h[i].end() == find(h[i].begin(),h[i].end(), j) )
		return false;
	else 
		return true;
}

DGraph& DGraph::Add(const int i, const int j)
{
	if( i < 1 || i > n || j < 1 || j > n || Exist(i, j) )
		//throw BadInput;
		;
	return AddNoCheck(i, j);
}

DGraph& DGraph::AddNoCheck( const int i, const int j )
{
	h[i].push_front(j);
	++e;
	return *this;
}

DGraph& DGraph::Del(const int i, const int j)
{
	if( i < 1 || i > n )
		/* throw OutOfBounds(); */
		;
	remove(h[i].begin(),h[i].end(),j);
	return *this;
}

int DGraph::InDegree(const int i) const
{
	if( i < 1 || i > n )
		/* throw OutOfBounds(); */
		;
	int sum = 0;
	for( int j = 1 ; j <= n ; ++j )
		if (Exist(i, j))
			++sum;
	return sum;	
}
#endif  /*DGRAPH_HPP*/
