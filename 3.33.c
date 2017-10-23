#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#define DEQUE_LEN 10
#define BCAKWARD(x) ((x)= ((x)+DEQUE_LEN-1)%DEQUE_LEN)
#define FORWARD(x) ((x)=((x)+1)%DEQUE_LEN)
#define GET(pD,i) ((pD)->data[(i)] )
#define HEAD(pD) GET(pD,pD->head)
#define REAR(pD)  GET(pD,pD->rear)
typedef struct{
	ElemType	*data;
	int head;
	int rear;
	int len;
	
}deque;
Status InitDeque(deque* D,int len);
Status EnDeque(deque* D,const ElemType *data );
Status DeDeque(deque* D,ElemType *data );
Status DestoryDeque(deque* D);
void OutputDeque(deque* D);

int main() {
	int i =0,t=0;
	int a[10]={1,2,3,5,6,-1,7,8,9,10};
	deque D ;
	InitDeque(&D,DEQUE_LEN);
	for(i=0;i<10;i++){
		EnDeque(&D, &a[i]);
		printf("[IN]:%2d\n",a[i]);
	}
	OutputDeque(&D);
	for(i=0;i<DEQUE_LEN;i++){
		DeDeque(&D, &t);
		printf("[OUT]%2d\n",t);
		}
	getchar();
	return 0;
}//main

Status InitDeque(deque* D,int len){
	if(D ==NULL) return INVALID_ARGUMENT;
	D->data = malloc(sizeof(ElemType)*len);
	memset(D->data,0,sizeof(ElemType)*len);
	D->head = 0;
	D->rear = 0;
	D->len = 0;
}//InitDeque

Status EnDeque(deque* D,const ElemType *data ){
	if(D ==NULL||data==NULL) return INVALID_ARGUMENT;
	if(D->len ==DEQUE_LEN ) return OVERFLOW;
	if(D->len==0){
		REAR(D) = *data ;
	}else if( (*data)*2 < ( HEAD(D)+REAR(D) ))
		GET(D,FORWARD(D->head))=  *data ;
	else
		GET(D,BCAKWARD(D->rear))= *data ;
	(D->len)++;
	return OK;
}//EnDeque

Status DeDeque(deque* D,ElemType *data ){
	if(D ==NULL||data==NULL) return INVALID_ARGUMENT;
	if(D->len == 0 ) return INFEASIBLE;
	*data = HEAD(D);
	BCAKWARD(D->head);
	(D->len)--;
	return OK;
}//DeDeque

void OutputDeque(deque* D){
	int i;
	for(i=0;i<DEQUE_LEN;i++){
		printf("%2d ",GET(D,i));
	}
	putchar('\n');
	printf("len:%d",D->len);
	putchar('\n');
}//OutputDeque
Status DestoryDeque(deque* D){
	if(D ==NULL) return INVALID_ARGUMENT;
	if(D->data ==NULL) return INFEASIBLE;
	free(D->data);
	D->data = NULL;
	D->head = 0;
	D->rear = 0;
	D->len = 0;
	return OK;
}//DestoryDeque


