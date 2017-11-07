#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitStack(LinerStack* S){
	if (!S) return INVALID_ARGUMENT;
	S->base=S->top=malloc(sizeof(S)* STACK_INIT_LEN);
	memset(S->base,0,(sizeof(S)* STACK_INIT_LEN));
	S->size=0;
	return OK;
}
Status PushStack(LinerStack* S,ElemType data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == STACK_INIT_LEN )return OVERFLOW;
	if(S->size!=0)(S->top)++;
	*(S->top) =data; 
	S->size++;
	return OK;
}

Status PopStack(LinerStack* S,ElemType* data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == 0)return INFEASIBLE;
    *data = *((S->top));
    if(S->size !=1)(S->top)--;

	S->size--;
	return OK;
}
Status GetTop(LinerStack* S){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == 0)return INFEASIBLE;
	
	return *(S->top);
}
void ShowStack(LinerStack* S,unsigned int limit){
	if (!S) return ;
	int len;
	if(limit)
		len = (S->size)%limit;
	len = S->size;
	while(len){
		printf("%c ",S->base[len-1]);
		if(S->base+(len-1)== S->top)
			printf("<-top");
		putchar('\n');
		len--;
	}
	printf("\n--- len:%d\n",S->size);
}
