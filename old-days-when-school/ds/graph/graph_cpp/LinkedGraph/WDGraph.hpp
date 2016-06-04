#ifndef  WDGRAPH_HPP
#define  WDGRAPH_HPP

template<class T>
class WDGraph:public GraphBase< GraphNode<T> >{
	public:
		WDGraph(int Vertices = 10) 
			:GraphBase< GraphNode<T> >(Vertices){}
		bool Exist(const int i, const int j) const;
		WDGraph<T>& Add(const int i, const int j, const T& w);
		WDGraph<T>& Del(const int i, const int j);
		int InDegree(int i) const;	
	protected:
		WDGraph<T>& AddNoCheck(const int i, const int j, const T& w);
	private:
}




#endif  /*WDGRAPH_HPP*/
