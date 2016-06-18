#ifndef _LINKSCREEN_H_
#define _LINKSCREEN_H_

#include "Screen.h"
#include <iostream>
#include <string>
using namespace std;

class LinkScreen{
	public:
	private:
	Screen		window;
	LinkScreen *next;
	LinkScreen *prev;	

};

#endif /*_LINKSCREEN_H_*/
