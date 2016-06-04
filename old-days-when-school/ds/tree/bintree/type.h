#ifndef _TYPE_H_
#define _TYPE_H_

#include "lueap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/errno.h>


#define		TRUE	1
#define		FALSE	0
#define		YES		1
#define		NO		0

struct BinTreeNode;
struct QNode;
struct SNode;

typedef struct BinTreeNode *ptrBTNode;

typedef char		__BTElemType;
#define BTElemType	__BTElemType
typedef ptrBTNode	__SElemType;
#define SElemType   __SElemType
typedef ptrBTNode	__QElemType;
#define QElemType	__QElemType

#endif /*_TYPE_H_*/
