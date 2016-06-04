#include <stack>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

class CTree {
public:
	typedef struct tagNode {
		char data;
		tagNode *lchild, *rchild;
	}Node, *pNode;
	
	CTree():root(NULL){
	}
	~CTree() {
		Destory();
	}

	void Create() {
		CreateHelp(root);
	}
	void CreateHelp(pNode& node) {
		char data;
		cin>>data;
		if ( data != '#' ) {
			node = new Node;
			node->data = data;
			CreateHelp(node->lchild);
			CreateHelp(node->rchild);
		}
		else
			node = NULL;
	}
	void Destory() {
		DestoryHelp(root);
	}
	void DestoryHelp(pNode& node) {
		if ( node ) {
			DestoryHelp(node->lchild);
			DestoryHelp(node->rchild);
			delete node;
			node = NULL;
		}
	}
	void PreOrderTraverse() {
		pNode cur = root;
		stack<pNode> S;
		while ( cur || !S.empty() )
		{
			while ( cur != NULL ) {
				cout<< cur->data <<" ";
				S.push(cur);
				cur = cur->lchild;
			}
			if ( !S.empty() )	
			{
				cur = S.top();
				S.pop();
				cur = cur->rchild;
			}
		}
		cout<<endl;
	}

	void InOrderTraverse() {
		pNode cur = root;
		stack<pNode> S;
		while ( cur || !S.empty() )
		{
			if ( cur )
			{
				S.push(cur);
				cur = cur->lchild;
			}
			else
			{
				cur = S.top();
				S.pop();
				cout<<cur->data<<" ";
				cur = cur->rchild;
			}
		}
		cout<<endl;
	}

	void PostOrderTraverse()
	{
		pNode cur;
		pNode pre = NULL;
		stack<pNode> S;
		if ( root )
			S.push(root);
		while ( !S.empty() )
		{
			cur = S.top();
			if( (cur->lchild == NULL&& cur->rchild == NULL) || ( pre != NULL && (pre == cur->lchild || pre == cur->rchild) ) )
			{
				cout<< cur->data <<" ";
				pre = cur;
				S.pop();
			}
			else
			{
				if ( cur->rchild )
					S.push(cur->rchild);
				if ( cur->lchild )
					S.push(cur->lchild);
			}
		}
		cout<<endl;
	}

	void LevelOrderTraverse()  {
		queue <pNode> Q;
		pNode cur;
		if (root)
			Q.push(root);
		while ( !Q.empty() )
		{
			cur = Q.front();
			Q.pop();
			cout<< cur->data <<" ";
			if ( cur->lchild )
				Q.push(cur->lchild);
			if ( cur->rchild )
				Q.push(cur->rchild);
		}
		cout<<endl;
	}

	void Pre() {
		pNode cur;
		stack <pNode> S;
		if (root)
			S.push(root);
		while ( !S.empty() )
		{
			cur = S.top();
			S.pop();
			cout<< cur->data <<" ";
			if ( cur->rchild )
				S.push(cur->rchild);
			if ( cur->lchild )
				S.push(cur->lchild);
		}
		cout<<endl;
	}
	
private:
	pNode root;
};

int main(void)
{
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);

	CTree T;
	T.Create();
	T.PreOrderTraverse();
	T.Pre();
	T.InOrderTraverse();
	T.PostOrderTraverse();
	T.LevelOrderTraverse();
	return 0;
}
