#include <iostream>
#include <fstream>
#include <algorithm>
#include "TextQuery.hpp"
#include "Query.hpp"

using namespace std;

void print_results(const set<TextQuery::line_no>& locs, 
		const string& sought, const TextQuery &file)
{
	typedef set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();

	cout << endl;
	cout << sought << " occurs " << size << " " /*<< make_plural(size, "time", "s")*/ << endl;
	line_nums::const_iterator it = locs.begin();
	for ( ; it != locs.end(); ++it)
		cout << "\t(line" << (*it) + 1 << ") " << file.text_line(*it) << endl;
}

int main (int argc, char **argv)
{
	ifstream infile;
	
	if (argc < 2 )
	{
		cerr << "No input file!" << endl;
		return EXIT_FAILURE;
	}

	infile.open(argv[1], std::ifstream::in);
	TextQuery tq;
	tq.read_file(infile);

	while (true)
	{
		cout << endl <<"Enter word to look for, or q to quit: " ;
		string	s;
		cin >> s;

		if (!cin || s == "q")
			break;
		set<TextQuery::line_no> locs = tq.run_query(s);

		print_results(locs, s, tq);
	}

	return 0;
}
