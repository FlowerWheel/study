#include	"list.hpp"


	template<class ElemType>
List<ElemType>::List(const List<ElemType>& list)
{
	*this = list;
	/*
	   ListNode<ElemType>	*cur = list.head;
	   ListNode<ElemType>	*node_pre = nullptr, **node = &head;

	   while(cur)
	   {
	   if ((*node = new ListNode<ElemType>(cur->element)) != nullptr)
	   {
	 *node->prev = node_pre;
	 node_pre = *node;
	 node = &(*node->next);
	 cur = cur->next;
	 }
	 }
	 tail = node_pre;
	 */
}

	template<class ElemType>
List<ElemType>& List<ElemType>::operator = (const List<ElemType>& list)
{	
	ListNode<ElemType>	*cur = list.head;
	ListNode<ElemType>	*node_pre = nullptr, **node = &head;

	while(cur)
	{
		if ((*node = new ListNode<ElemType>(cur->element)) != nullptr)
		{
			*node->prev = node_pre;
			node_pre = *node;
			node = &(*node->next);
			cur = cur->next;
			++size;
		}
	}
	tail = node_pre;

}

	template<class ElemType>
void List<ElemType>::Push_Front(const ElemType &e)
{
	ListNode<ElemType>	*front = new ListNode<ElemType>;
	front->element = e;
	front->prev = nullptr;
	front->next = head;
	++size;
	if (!Empty())
	{
		head->prev = front;
		head = front;
	}
	else
		head = tail = front;
}
	template<class ElemType>
void List<ElemType>::Push_Back(const ElemType &e)
{
	ListNode<ElemType>	*back = new ListNode<ElemType>;
	back->element = e; 
	back->next = nullptr;
	back->prev = tail;
	++size;
	if (!Empty())
	{
		tail->next = back;
		tail = back;
	}
	else 
		head = tail = back;
}

	template<class ElemType>
ElemType List<ElemType>::Pop_Front(void)
{
	if (!Empty())
	{
		ListNode<ElemType> *front = head;
		head = head->next;
		head->prev = nullptr;
		delete front;
		--size;
	}
}
	template<class ElemType>
ElemType List<ElemType>::Pop_Back(void)
{
	if (!Empty())
	{
		ListNode<ElemType> *back = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete back;
		--size;
	}
}

template<class T>
ostream& operator << (ostream& os, const ListNode<T>& node)
{
	os << node.element;
	return os;
}

template<class ElemType>
ostream& operator << (ostream& os, const List<ElemType>& list)
{
	ListNode<ElemType>	*node = list.head;
	while(node)
	{
		os << *node << " ";
		node = node->get_next();
	}
	return os;
}

	template<class ElemType>
void List<ElemType>::DelList(void)
{
	ListNode<ElemType>	*cur;
	while (cur = head, cur != nullptr)
	{
		head = head->next;
		delete cur;
	}
	tail = nullptr;
}

#define  TEST


#ifdef TEST

#include	<iostream>

int main (void)
{
	List<int>	list_int;

	for (int i = 0; i < 10; ++i)
		list_int.Push_Back(i);

	std::cout << list_int.Size() << std::endl; 
	std::cout << list_int << std::endl;
	return 0;
}

#endif
