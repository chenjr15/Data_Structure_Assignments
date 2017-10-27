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
Status PushStack(LinerStack* S,ElemType data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == STACK_INIT_LEN )return OVERFLOW;
	S->base[S->size++] =data;
	return OK;
}

Status PopStack(LinerStack* S,ElemType* data){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == 0)return INFEASIBLE;
    *data = S->base[--(S->size)];
	return OK;
}
Status GetTop(LinerStack* S){
	if (!S) return INVALID_ARGUMENT;
	if(S->size == 0)return INFEASIBLE;
	
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
        switch  (S->base[len-1].type ){
            case OPERATOR_T:
                printf("%c ",S->base[--len]);
                break;
            case INTEGER_T:
                printf("%d ",S->base[--len]);
                break;
            case FLOAT_T:
                printf("%g ",S->base[--len]);
                break;
        }

		putchar('\n');
	}
	printf("[ end ]\n");
}
