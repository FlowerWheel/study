#ifndef _LEFTHEAP_H_
#define _LEFTHEAP_H_

struct TreeNode;
typedef struct TreeNode *PriorityQueue;

typedef int	ElemType;

PriorityQueue InitLH(void);
ElemType FindMinLH(PriorityQueue LH);
int	IsEmptyLH(PriorityQueue LH);
PriorityQueue MergeLH(PriorityQueue LH1, PriorityQueue LH2);

PriorityQueue Insert1LH(PriorityQueue *LH, ElemType x);
PriorityQueue DeleteMin1LH(PriorityQueue *LH);

#endif /*_LEFTHEAP_H_*/

struct TreeNode {
	ElemType		data;
	PriorityQueue	left;
	PriorityQueue	right;
	int				npl;
};
