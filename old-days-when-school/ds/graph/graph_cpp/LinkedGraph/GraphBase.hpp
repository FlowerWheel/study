#ifndef  GRAPHBASE_HPP
#define  GRAPHBASE_HPP

#include  <list>
using std::list;

template<class T>
class GraphBase{
	public:
		GraphBase(int Vertices = 10)
			:n(Vertices), e(0) {
				h = new list<T>[n + 1];
			}
		~GraphBase(){ delete [] h; }
		int Edges() const { return e; }
		int Vertices() const { return n; }
		int OutDegree(const int i) const
		{
			if( i < 1 || i > n )
				;
			return h[i].lenth();
		}
	protected:
		int		n;
		int		e;
		list<T> *h;
	private:
};



#endif  /*GRAPHBASE_HPP*/
