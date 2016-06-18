#include "Sales_item.h"
#include <iostream>
#include <string>


int main (int argc, char **argv)
{
	
    Sales_item	item1;
	Sales_item  item2 = Sales_item();
	//Sales_item  item3 = string("0-201-54848-8");//error
	Sales_item  item4(string("0-201-54848-8"));
	Sales_item  item5(cin);
	return 0;
}
