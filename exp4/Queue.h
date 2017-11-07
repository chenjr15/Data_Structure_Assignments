#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "common.h"
#define DEQUE_LEN 200
#define BCAKWARD(x) ((x)= ((x)+DEQUE_LEN-1)%DEQUE_LEN)
#define FORWARD(x) ((x)=(((x)+1)%DEQUE_LEN))
#define GET(pD,i) ((pD)->data[(i)] )
#define HEAD(pD) GET(pD,pD->head)
#define REAR(pD)  GET(pD,pD->rear)
typedef struct{
	SElemType	*data;
	int head;
	int rear;
	int len;
	
}deque;
Status InitDeque(deque* D,int len);
Status EnDeque(deque* D,const SElemType *data );
Status DeDeque(deque* D,SElemType *data );
Status DestoryDeque(deque* D);
void OutputDeque(deque* D);
#endif