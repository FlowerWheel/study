#ifndef DEQUE_H
#define DEQUE_H

#include <cstdlib>

template <typename T>
class Deque
{
	typedef struct ListNode
	{
		T elem;
		ListNode * prev;
		ListNode * next;
	} ListNode, * LinkList;
private:
	LinkList Front;
	LinkList Rear;
public:
	Deque ( )
	{
		Front = Rear = NULL;
	}
	~Deque()
	{
		LinkList p = Front;
		while ( p != NULL )
		{
			Front = p->next;
			delete p;
			p = Front;
		}
		Rear = NULL;
	}
	bool isEmpty() const
	{
		return (Front == NULL);
	}
	void push_back( const T & e )
	{
		LinkList p = new ListNode;
		p->elem = e;
		p->prev = NULL;
		p->next = NULL;
		if ( isEmpty() )
			Front = Rear = p;
		else
		{
			Rear->next = p;
			p->prev = Rear;
			Rear = p;
		}
	}
	void push_front( const T & e )
	{
		LinkList p = new ListNode;
		p->elem = e;
		p->prev = NULL;
		p->next = NULL;
		if ( isEmpty() )
			Front = Rear = p;
		else
		{
			Front->prev = p;
			p->next = Front;
			Front = p;
		}
	}
	void pop_front()
	{
		LinkList p = Front;
		Front = p->next;
		delete p;
	}
	void pop_back()
	{
		LinkList p = Rear;
		Rear = p->prev;
		delete p;
	}
	T & front() const
	{
		return Front->elem;
	}
	T & back() const
	{
		return Rear->elem;
	}
};

#endif
