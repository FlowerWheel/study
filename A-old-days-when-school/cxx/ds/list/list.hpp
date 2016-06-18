#ifndef  LIST_HPP
#define  LIST_HPP

#include	<ostream>
#include	<cstdlib>

using std::ostream;

template<class ElemType> class List;

template<class ElemType> class ListNode{
	public:
		typedef ListNode<ElemType>	Node;
		friend class List<ElemType>;

		ListNode(ElemType e = 0, Node * p = nullptr, Node * n = nullptr)
			:element(e), prev(p), next(n) {}
		ListNode(const Node &node)
			:element(node.element), prev(node.prev), next(node.next) {}
		ListNode& operator = (const Node &node)
		{
			element	= node.element;
			prev	= node.prev;
			next	= node.next;
			return *this;
		}
		~ListNode()
		{
			if (next) delete next;
		}

		template<class T>
		friend ostream& operator << (ostream&, const ListNode<T>&);

		/* ListNode<ElemType> * operator ->() { return this->ptr;}  */

		ListNode<ElemType> * get_prev(void) const { return prev; }
		ListNode<ElemType> * get_next(void) const { return next; }

	private:
		ElemType	element;
		Node		*prev;
		Node		*next;
};

template<class ElemType> class List{
	public:
		typedef	size_t		size_type;

		/*Constructors*/
		List(void):size(0), head(nullptr), tail(nullptr) {}
		List(const List<ElemType>& list);

		/*DeConstructors*/
		~List() { DelList(); }

		/*Operator =*/
		List<ElemType>& operator = (const List<ElemType>& list);

		/*Capacity*/
		bool		Empty(void) const {return (size == 0);}
		size_type	Size(void) const {return size;}

		ElemType	Front(void) const { if (!Empty()) return head->element; }
		ElemType	Back(void) const { if (!Empty()) return tail->element; }

		void		Push_Front(const ElemType &e);

		void		Push_Back(const ElemType &e);

		ElemType	Pop_Front(void);
		ElemType	Pop_Back(void);

		void		Insert();
		void		Erease();
		void		Clear(void);
		void		Resize(void);

		template<class T>
		friend ostream& operator << (ostream& os, const List<T>& list);


	private:
		size_type			size;
		ListNode<ElemType>	*head;
		ListNode<ElemType>	*tail;

		void DelList(void);
};

#endif  /*LIST_HPP*/
