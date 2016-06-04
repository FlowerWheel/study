#ifndef _ADJWDGRAPH_
#define _ADJWDGRAPH_

template <class T>
class AdjWDGraph{
//	friend AdjWGraph<T>;
	public:
		/* AdjWDGraph(); // no necessary */
		AdjWDGraph(int Vertices = 10, T noEdge = 0)
			:n(Vertices), e(0), NoEdge(noEdge)
	   	{
			Make2DArray(a, n+1, n+1); 
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					a[i][j] = NoEdge;
		}	 
		~AdjWDGraph(){ Delete2DArray(a, n+1); } /* DeConstructor */  

		bool Exist(const int i, const int j) const;		
		const T& Weight(const int i, const int j) const;
		int  Edges() const { return e; }
		int	 Vertices() const { return n; }

		AdjWDGraph<T>& Add(const int i, const int j, const T& w);
		AdjWDGraph<T>& Del(const int i, const int j);
         
		int InDegree(int i) const;
		int OutDegree(int i) const;

	protected:
		int n;
		int e;
		T	NoEdge;
		T	**a;

	private:
		void Make2DArray(T **&arr, int rows, int cols)
		{ 
			arr = new T* [rows];
			for( int i = 0 ; i < rows ; ++i )
				arr[i] = new T[cols];
			
		}
		void Delete2DArray(T **&arr, int rows)
		{ 
			for( int i = 0 ; i < rows ; ++i )
				delete [] arr[i];
			delete [] arr; 
		}
 
};

template<class T>
bool AdjWDGraph<T>::Exist(const int i, const int j) const
{
	if (i < 1 || j < 1 || i > n || j > n || a[i][j] == NoEdge)
		return false;
	else 
		return true;
}

template<class T>
const T& AdjWDGraph<T>::Weight(const int i, const int j) const
{
	if (i < 1 || j < 1 || i > n || j > n)
		return NoEdge;
	else 
		return a[i][j];
}

template<class T>
AdjWDGraph<T>& AdjWDGraph<T>::Add(const int i, const int j, const T& w)
{
	if (!Exist(i, j) || i == j)
	//	throw BadInput();
		;
	a[i][j] = w;
	++e;
	return *this;
}

template<class T>
AdjWDGraph<T>& AdjWDGraph<T>::Del(const int i, const int j)
{
	if (!Exist(i, j) || i == j)
	//	throw BadInput();
		;
	a[i][j] = NoEdge;
	--e;
	return *this;
}

template<class T>
int AdjWDGraph<T>::InDegree(const int i) const
{
	if (i < 1 || i > n)
		;
	//	throw BadInput();
	int sum = 0;
	for (int j = 1; j <= n; j++)
		if (a[i][j] != NoEdge)
			++sum;
	return sum;
}

template<class T>
int AdjWDGraph<T>::OutDegree(const int i) const
{
	if (i < 1 || i > n)
		;
		//throw BadInput();
	int sum = 0;
	for (int j = 1; j <= n; j++)
		if (a[j][i] != NoEdge)
			++sum;
	return sum;
}


#endif
