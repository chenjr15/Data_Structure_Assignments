#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "common.h"
#define QUEUE_LEN 200
#define BCAKWARD(x) ((x)= ((x)+QUEUE_LEN-1)%QUEUE_LEN)
#define FORWARD(x) ((x)=(((x)+1)%QUEUE_LEN))
#define GET(pD,i) ((pD)->data[(i)] )
#define HEAD(pD) GET(pD,pD->head)
#define REAR(pD)  GET(pD,pD->rear)

Status InitQueue(queue* D,int len);
Status EnQueue(queue* D,const SElemType *data );
Status DeQueue(queue* D,SElemType *data );
Status DeQueueR(queue* D,SElemType *data );
Status DestoryQueue(queue* D);
void OutputQueue(queue* D);
Status IsInQueue(queue* Q,SElemType* data);
#endif