#ifndef  QUERY_HPP
#define  QUERY_HPP

#include <set>
#include <algorithm> 
#include <iostream>
#include "TextQuery.hpp"

using namespace std;

class Query_base{
	private:
		friend	class Query; 
	protected:
		typedef		TextQuery::line_no line_no;
		virtual		~Query_base() {}
	private:
		virtual std::set<line_no> 
			eval(const TextQuery& tq) const = 0;
		virtual std::ostream& 
			display(ostream& = cout) const = 0;
};

class Query{
	private:
		friend Query operator ~ (const Query &);
		friend Query operator | (const Query &, const Query &);
		friend Query operator & (const Query &, const Query &);

	public:
		Query(const string&);
		Query(const Query &c):q(c.q), use(c.use){++*use;}
		~Query(){decr_use();}
		Query& operator = (const Query&);

		set<TextQuery::line_no>
			eval(const TextQuery& t) const {return q->eval(t);}
		ostream& 
			display(ostream &os) const {return q->display(os);}

	private:
		Query(Query_base *query):q(query), use(new size_t(1)){}

		Query_base	*q;
		size_t		*use;
		void		decr_use(){ if (--*use == 0) {delete q; delete use;}}
};

inline ostream&operator<<(ostream &os, const Query& q)
{
	return q.display(os);
}

class WordQuery:public Query_base{
	private:
		friend class Query;

		WordQuery(const string &s):query_word(s) {}

		/*redefine Base Class virtual function*/
		set<line_no> 
			eval(const TextQuery& t) const { return t.run_query(query_word); }
		ostream& 
			display(ostream& os) const { return os << query_word; }

		string query_word;
};

Query::Query(const string& s)
	:q(new WordQuery(s)), use(new size_t(1)){}

class NotQuery:public Query_base{
	private:
		friend class Query;
		friend Query operator ~ (const Query &);

		NotQuery(Query q):query(q){}

		/*redefine Base Class virtual function*/
		set<line_no> 
			eval(const TextQuery& file) const
			{
				set<line_no> has_val = query.eval(file);
				set<line_no> ret_lines;
				for (line_no n = 0; n != file.size(); ++n)
				{
					if (has_val.find(n) == has_val.end())
						ret_lines.insert(n);
				}
				return ret_lines;
			}
		ostream& 
			display(ostream& os) const
			{
				return os << "~(" << query << ")";
			}

		const Query query;
};

class BinQuery:public Query_base{
	protected:
		BinQuery(Query left, Query right, string op):
			lhs(left), rhs(right), oper(op){}

		/*redefine Base Class virtual function*/
		ostream& display(ostream& os) const
		{
			return os << "(" << lhs << " " << oper << " " << rhs << ")";
		}

		const Query lhs, rhs;
		const string oper;
};

class AndQuery:public BinQuery{
	private:
		friend Query operator & (const Query&, const Query&);

		AndQuery(Query left, Query right):BinQuery(left, right, "&"){}

		/*redefine Base Class virtual function*/
		set<line_no> eval(const TextQuery& file) const
		{
			set<line_no> left = lhs.eval(file), 
				right = rhs.eval(file);

			set<line_no> ret_lines;

			set_intersection(
					left.begin(), left.end(), 
					right.begin(), right.end(),
					inserter(ret_lines, ret_lines.begin()));
			return ret_lines;
		}
};

class OrQuery:public BinQuery{
	private:
		friend Query operator | (const Query&, const Query&);

		OrQuery(Query left, Query right):BinQuery(left, right, "|"){}

		/*redefine Base Class virtual function*/
		set<line_no> eval(const TextQuery& file) const
		{
			set<line_no> right = rhs.eval(file), 
				ret_lines = lhs.eval(file);
			ret_lines.insert(right.begin(), right.end());
			return ret_lines;
		}
};

inline Query operator & (const Query &lhs, const Query &rhs)
{
	return new AndQuery(lhs, rhs);
}

inline Query operator | (const Query &lhs, const Query &rhs)
{
	return new OrQuery(lhs, rhs);
}

inline Query operator ~ (const Query &oper)
{
	return new NotQuery(oper);
}
#endif  /*QUERY_HPP*/
