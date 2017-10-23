#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"
#define QUEUE_INIT_LEN 20
typedef struct{
	LNode head;
	LNode * rear;
	int len;
}queue;
Status InitQueue(queue* Q,int len);
Status DestoryQueue(queue* Q,int len);
Status EnQueue(queue* Q,const ElemType *data );
Status DeQueue(queue* Q,ElemType *data );
void OutputQueue(queue* Q);
int main(){
	int i = 0,t=0;
	queue Q;
	InitQueue(&Q,QUEUE_INIT_LEN);
	for(i=1;i<=2*QUEUE_INIT_LEN+1;i+=2){
		switch (EnQueue(&Q, &i)){
			case OK:
				printf("pushing: %d, len: %d\n",i,Q.len);
				break;
			case INVALID_ARGUMENT:
				printf("INVALID_ARGUMENT, len: %d\n",Q.len);
				break;
			case OVERFLOW:
				printf("OVERFLOW, len: %d\n",Q.len);
				break;
		}
	//OutputQueue(&Q);
	}
	for(i=0;i<QUEUE_INIT_LEN+2;i++){
		switch (DeQueue(&Q, &t)){
			case OK:
				printf("poping: %d, len: %d\n",t,Q.len);
				break;
			case INVALID_ARGUMENT:
				printf("INVALID_ARGUMENT, len: %d\n",Q.len);
				break;
			case INFEASIBLE:
				printf("INFEASIBLE, len: %d\n",Q.len);
				break;
		}
	//OutputQueue(&Q);
	}
	DestoryQueue(&Q);
	
	return 0;
}


Status InitQueue(queue* Q,int len){
	if(len<1||Q==NULL) return INVALID_ARGUMENT;
	
	Q->head.next = Q->rear = CreateNode(0,NULL);
	Q->rear->next = Q->rear;
	Q->len=0;
	len--;
	while(len--){
		Q->rear->next= CreateNode(0,Q->head.next);
		Q->rear=Q->rear->next;
		
	}
	return OK;
}//InitQueue

Status EnQueue(queue* Q,const ElemType *data ){
	if(data == NULL||Q==NULL)return INVALID_ARGUMENT;
	if((Q->len+1)>QUEUE_INIT_LEN) return OVERFLOW;
	Q->rear->next->data =*data;
	Q->rear= (Q->rear->next);
	Q->len++;
	return OK;
	
}//EnQueue
Status DeQueue(queue* Q, ElemType *data ){
	if(data == NULL||Q==NULL)return INVALID_ARGUMENT;
	if(Q->len<1) return INFEASIBLE;
	*data = Q->head.next->data;
	Q->head.next =	Q->head.next->next;
	Q->len--;
	return OK;
	
}//DeQueue
Status DestoryQueue(queue* Q,int len){
	if(Q==NULL||len<0)return INVALID_ARGUMENT;
	LNode *p,*t;
	p=Q->head.next;
	while(len--){
		t=p;
		p=p->next;
		free(t);
	}
	
}//DestoryQueue
void OutputQueue(queue* Q){
	LNode *p=Q->head.next;
	do{
		printf("%d ",p->data);
		p=p->next;	
	}while(p!= Q->head.next);
	putchar('\n');
}//OutputQueue

