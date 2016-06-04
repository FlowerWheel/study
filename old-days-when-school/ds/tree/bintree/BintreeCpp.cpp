//#include "bintree.h"
#ifndef BINTREE_H
#define BINTREE_H

#include "iostream"
#include <stack>
#include <queue>

using namespace std;

template <typename ElemType>
class CBinTree {

	private:
		typedef struct tagBinTreeNode {
			ElemType				data;
			struct tagBinTreeNode*	plChild;
			struct tagBinTreeNode*	prChild;
		}BinTreeNode, *pBinTreeNode;

	public:
		CBinTree()
		{
			m_pHead = NULL;
		}
		virtual ~CBinTree()
		{
			Destroy(m_pHead);
		}
		void PreCreateBinTree(pBinTreeNode& T)
		{
			char ch;
			cin>>ch;
			if (ch != '#')
			{
				T = new BinTreeNode;
				T->data = ch;
				PreCreateBinTree(T->plChild);
				PreCreateBinTree(T->prChild);
			}
			else
				T = NULL;
		}
		void nonRecursivePreOrderTraverse(void (*visit)(const ElemType &)) const
		{
			stack<pBinTreeNode> S;
			pBinTreeNode current;
			if (m_pHead)
				S.push(m_pHead);
			while(!S.empty())
			{
				while ((current = S.top()), current)
				{
					visit (current->data);
					S.push(current->plChild);
				}
				S.pop();
				if (!S.empty())
				{
					current = S.top();
					S.pop();
					S.push(current->prChild);
				}
			}
		}
		void nonRecursiveInOrderTraverse(void (*visit)(const ElemType &)) const
		{
			stack<pBinTreeNode> S;
			pBinTreeNode current;
			if (m_pHead)
				S.push(m_pHead);
			while(!S.empty())
			{
				while ((current = S.top()), current)
					S.push(current->plChild);
				S.pop();
				if ( !S.empty())
				{
					current = S.top();
					S.pop();
					visit (current->data);
					S.push(current->prChild);
				}
			}
		}
		void nonRecursivePostOrderTraverse(void (*visit)(const ElemType &)) const
		{
			stack<pBinTreeNode> S, b;
			pBinTreeNode current;
			if (m_pHead)
				S.push(m_pHead);
			while(!S.empty())
			{
				while ((current = S.top()), current)
				{
					S.push(current->prChild);
				}
				S.pop();
				if (!S.empty())
				{
					current = S.top();
					if (S.top() == b.top())
						S.pop();
					else {
						b.push(current);
						visit (current->data);
						S.push(current->plChild);
					}
				}
			}
		}
		void PostOrderTraverse(const pBinTreeNode T, void (*visit)(const ElemType &)) const
		{
			if (T)
			{
				PostOrderTraverse(T->plChild, visit);
				PostOrderTraverse(T->prChild, visit);
				visit(T->data);
			}
		}
		void PreOrderTraverse(const pBinTreeNode T, void (*visit)(const ElemType &)) const
		{
			if (T)
			{
				visit(T->data);
				PreOrderTraverse(T->plChild, visit);
				PreOrderTraverse(T->prChild, visit);
			}
		}
		void InOrderTraverse(const pBinTreeNode T, void (*visit)(const ElemType &)) const
		{
			if (T)
			{
				InOrderTraverse(T->plChild, visit);
				visit(T->data);
				InOrderTraverse(T->prChild, visit);
			}
		}
		void LevelOrderTraverse( void (*visit)(const ElemType &) ) const
		{
			queue <pBinTreeNode> Q;
			pBinTreeNode pCurrent;
			Q.push( m_pHead );
			while ( !Q.empty() )
			{
				pCurrent = Q.front();
				Q.pop();
				visit(pCurrent->data);
				if ( pCurrent->plChild )
					Q.push( pCurrent->plChild);
				if ( pCurrent->prChild )
					Q.push( pCurrent->prChild);
			}
		}
		void Destroy(pBinTreeNode& T)
		{
			if (T)
			{
				Destroy(T->plChild);
				Destroy(T->prChild);
				delete T;
				T = NULL;
			}
		}
		pBinTreeNode m_pHead;
};

#endif // BINTREE_H

void print(const char& ch)
{
	cout<<ch<<" ";
}

int main(void)
{
	CBinTree<char> T;
	T.PreCreateBinTree(T.m_pHead);

	T.PreOrderTraverse(T.m_pHead, print);
	cout<<endl;
	T.InOrderTraverse(T.m_pHead, print);
	cout<<endl;
	T.PostOrderTraverse(T.m_pHead, print);
	cout << endl;
	cout << endl;

	T.nonRecursivePreOrderTraverse(print);
	cout<<endl;
	T.nonRecursiveInOrderTraverse(print);
	cout<<endl;
	//	T.nonRecursivePostOrderTraverse(print);
	cout<<endl;
	cout << endl;

	T.LevelOrderTraverse(print);
	cout << endl;
	return 0;
}
/*abc##d##e##
 *   a
 *  b e
 * c d 
 *
 * */
