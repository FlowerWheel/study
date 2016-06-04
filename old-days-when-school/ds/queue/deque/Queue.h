#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template <typename T>
class Queue
{
private:
	Deque <T> c;
public:
	void pop()
	{
		c.pop_front();
	}
	void push( const T & e )
	{
		c.push_back(e);
	}
	T & top() const
	{
		return c.front();
	}
	bool IsEmpty() const
	{
		return c.IsEmpty();
	}
};

#endif
