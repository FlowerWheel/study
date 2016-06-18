#include   "GraphBase.hpp"
#include   <iostream>
#include   "DGraph.hpp"
#include   "Graph.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	DGraph	dg;
	cout << dg.Vertices() << endl;
	cout << dg.Edges() << endl;

	dg.Add(1, 2);
	dg.Add(1, 3);
	dg.Add(1, 4);
	cout << dg.Edges() << endl;
	cout << dg.InDegree(0) << endl;
	return 0;
}
