#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <iostream>
#include <string>
#include "Window_Mgr.h"

using namespace std;

class Screen{
	public:
		typedef std::string::size_type	index;

		Screen(index hg, index wd, string contains)
			:s_contents(contains), s_height(hg), s_width(wd){}

		char get() const
		{
			return s_contents[s_cursor];
		}

		inline char get(index ht, index wd) const;

		inline index get_cursor() const;

		Screen& display(ostream &os)
		{
			do_display(os);
			return *this;
		}

		const Screen& display(ostream &os) const
		{
			do_display(os);
			return *this;
		}

		void move(index hg, index wd)
		{
			s_height = hg;
			s_width = wd;
		}

		void set(char ch)
		{
			;
		}
		friend class Window_Mgr;
	private:
		void do_display(std::ostream &os) const
		{
			++s_access_ctr;
			os << s_contents;
		}
		mutable	size_t s_access_ctr;
		std::string s_contents;
		index		s_cursor;
		index		s_height, s_width;
};

inline Screen::index Screen::get_cursor() const
{
	return s_cursor;
}
#endif  /*_SCREEN_H_*/
