#include <iostream>
using namespace std;

class CBinTree{
	typedef struct tagNode {
		char data;
		tagNode *plChild; 
		tagNode *prChild;
	}Node, *pNode;
public:
	CBinTree():m_pRoot(NULL) {
	}
	~CBinTree() {
		Destory(m_pRoot);
	}
	void Create(pNode& node){
		char data;
		cin>data;
		if (data != '#'){
			node = new Node;
			node->data = data;
			Create(node->plChild);
			Create(node->prChild);
		}
		else
			node = NULL;
	}
	void preOrderTraverse(pNode node) {
		if (node) {
			cout<<node->data<<" ";
			preOrderTraverse(node->plChild);
			preOrderTraverse(node->prChild);
		}
	}
	void Destory(pNode& node){
		if (node){
			Destory(node->plChild);
			Destory(node->prChild);
			delete node;
		}
	}
	pNode getLCA(pNode root, pNode x, pNode y){
		if (root == NULL)
			return NULL;
		if (x == root || y == root)
			return root;
		pNode* left = getLCA(root->plChild, x, y);
		pNode* right = getLCA(root->prChild, x, y);
		if (left == NULL)
			return right;
		else if (right == NULL)
			return left;
		else
			return root;
	}
	pNode m_pRoot;
}

int main(void)
{
	CBinTree T;
	T.Create(T.m_pRoot);
	T.preOrderTraverse(T.m_pRoot);
	T.
	return 0;
}
