#ifndef _SALESITEM_H_
#define _SALESITEM_H_

#include <iostream>
#include <string>

using namespace std;

class Sales_item{
	public:
		//Sales_item() const; // un-necessary
		//Sales_item(): units_sold(0), revenue(0.0){}
		
		Sales_item() 
			:isbn(string(13, '0')), units_sold(0), revenue(0.0) { }
		explicit Sales_item(const string& book)
			: isbn(book), units_sold(0), revenue(0.0){ }
		Sales_item(const Sales_item &orig)
			: isbn(orig.isbn), units_sold(orig.units_sold), revenue(orig.revenue){ }
		Sales_item & operator = (const Sales_item &orig)
		{
			isbn = orig.isbn;
			units_sold = orig.units_sold;
			revenue = orig.revenue;
			return *this;
		}

		~Sales_item(){}

		explicit Sales_item(istream &is);

		inline double	avg_price() const;

		bool	same_isbn(const Sales_item &rhs) const
		{
			return isbn == rhs.isbn;
		}


	private:
		std::string isbn;
		unsigned	units_sold;
		double		revenue;
};

Sales_item::Sales_item(istream& is)
{
	is >> isbn;	
}
inline double Sales_item :: avg_price() const
{
	if (units_sold)
		return revenue / units_sold;
	else 
		return 0;
}

#endif
