#include <iostream>
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

	string s("The freedom");

	Query q = Query("The") | Query("freedom");

	set<TextQuery::line_no> line_nums = q.eval(tq);
	print_results(line_nums, s, tq);

	return 0;
}
