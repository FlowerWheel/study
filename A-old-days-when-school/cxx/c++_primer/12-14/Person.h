#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
using namespace std;

class Person{
	public:
		Person(int num, string name, string addr, unsigned age)
			:p_num(num), p_name(name), p_addr(addr), p_age(age)
		{}
		string get_name() const
		{
			return p_name;
		}
		string get_addr() const
		{
			return p_addr;
		}

	private:
		int				p_num;
		std::string		p_name;
		std::string		p_addr;
		unsigned		p_age;
};
#endif
