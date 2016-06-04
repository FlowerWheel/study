#include    "AdjWDGraph.hpp"
#include	"AdjDGraph.hpp"
#include	"AdjWGraph.hpp"
#include	"AdjGraph.hpp"
#include    <iostream>

using namespace std;

const int VNUM = 20;

int main(int argc, char *argv[])
{

	AdjWDGraph<int>	awdg(VNUM, 0);

	cout << awdg.Edges() << endl; 	
	cout << awdg.Vertices() << endl;
	cout << endl;

	awdg.Add(1, 2, 10);
	cout << awdg.Exist(1, 2) << endl;
	cout << awdg.Weight(1, 2) << endl;

	awdg.Del(1, 2);
	cout << awdg.Exist(1, 2) << endl;
	cout << awdg.Weight(1, 2) << endl;

	cout << endl;

	for( int i = 1 ; i < 10 ; ++i )
	{
		awdg.Add(11, i, i);
		awdg.Add(i, 8, i);
	}
	cout << awdg.InDegree(9) << endl;
	cout << awdg.InDegree(8) << endl;
	cout << awdg.OutDegree(9) << endl;
	cout << awdg.OutDegree(8) << endl;

	for( int i = 0 ; i < VNUM ; ++i )
	{	
		for( int j = 0 ; j < VNUM ; ++j )
			cout << awdg.Weight(i, j) << " ";
		cout << endl;
		
	}
	cout << endl;

	/*********************************************/

	cout << "*********************************" << endl;
	AdjDGraph	adg(VNUM);

	cout << adg.Edges() << endl;
	cout << adg.Vertices() << endl;

	adg.Add(1, 2);
	cout << adg.Exist(1, 2) << endl;
//	cout << adg.Weight(1, 2) << endl;
	adg.Del(1, 2);
	cout << adg.Exist(1, 2) << endl;

	for( int i = 1 ; i <= 10 ; ++i )
	{
		adg.Add(9, i);
		adg.Add(i, 8);
	}

	for( int i = 0 ; i < VNUM ; ++i )
	{	
		for( int j = 0 ; j < VNUM ; ++j )
			cout << adg.Exist(i, j) << " ";
		cout << endl;
		
	}
	cout << endl;

	/*********************************************/

	cout << "************************************" << endl;
	AdjWGraph<int>	awg(VNUM, 0);

	cout << awg.Edges() << endl;
	cout << awg.Vertices() << endl;

	awg.Add(1, 2, 3);
	cout << awg.Exist(1, 2) << endl;
	cout << awg.Weight(1, 2) << endl;
	cout << awg.Degree(1) << endl;
	cout << awg.Degree(2) << endl;
	awg.Del(1, 2);
	cout << awg.Exist(1, 2) << endl;
	cout << endl;
	
	/*********************************************/

	cout << "************************************" << endl;
	AdjGraph ag(VNUM);

	cout << ag.Edges() << endl;
	cout << ag.Vertices() << endl;

	ag.Add(1, 2);
	cout << ag.Exist(1, 2) << endl;
	cout << ag.Weight(1, 2) << endl;
	cout << ag.Degree(1) << endl;
	cout << ag.Degree(2) << endl;
	ag.Del(1, 2);
	cout << ag.Exist(1, 2) << endl;
	cout << endl;

	return 0;
}
