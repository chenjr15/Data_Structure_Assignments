//
// Created by hasee on 10/27 027.
//

#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitStack(LinerStack* S){
	if (!S) return INVALID_ARGUMENT;
	memset(S->base,0,(sizeof(S)* STACK_INIT_LEN));
	S->size=0;
	return OK;
}
Status PushStack(LinerStack* S, SElemType data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == STACK_INIT_LEN )return OVERFLOW_S;
	S->base[(S->size)++] =data;
	return OK;
}

Status PopStack(LinerStack* S, SElemType* data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == 0)return INFEASIBLE_S;
    *data = S->base[--(S->size)];
	return OK;
}
SElemType GetTop(LinerStack* S){
	if (!S) return 0;
	if(S->size == 0)return 0;
	
	return  S->base[(S->size)-1];
}
void ShowStack(LinerStack* S,unsigned int limit){
	if (!S) return ;
	int len;
	if(limit)
		len = (S->size)%limit;
	else
        len = S->size;
    printf("\n[ len:%d ]\n",S->size);
	while(len){
    printf("%c ",(int)S->base[--len]);
		putchar('\n');
	}
	printf("[ end ]\n");
}
