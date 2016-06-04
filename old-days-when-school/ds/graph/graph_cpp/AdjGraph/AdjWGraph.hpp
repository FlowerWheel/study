#ifndef _ADJWGRAPH_HPP_
#define _ADJWGRAPH_HPP_

template<class T>
class AdjWGraph:public AdjWDGraph<T>{
	public:
		AdjWGraph(int Vertices = 0, T noEdge = 0)
			:AdjWDGraph<T>(Vertices, noEdge){}
		/* ~AdjWGraph() */
		// { AdjWDGraph<T>::~AdjWDGraph(); }
		
		AdjWGraph& Add(const int i, const int j, const T& w)
		{
			AdjWDGraph<T>::Add(i, j, w);
			AdjWDGraph<T>::a[j][i] = w;
			return *this;
		}
		AdjWGraph& Del(const int i, const int j)
		{
			AdjWDGraph<T>::Del(i, j);
			AdjWDGraph<T>::a[j][i] = AdjWDGraph<T>::NoEdge;
			return *this;
		}
		int Degree(const int i) const
		{ return AdjWDGraph<T>::OutDegree(i); }
	private:
};

#endif /*_ADJWGRAPH_HPP_*/
