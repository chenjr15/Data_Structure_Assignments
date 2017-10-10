/**
 *  \file 2.10.c
 *  \author ChenJR
 *  错误：
 *    原算法在左移元素的时候从后往前移，
 *  前面的元素会被后面的元素覆盖而造成数据丢失
 *  低效：
 *    每删一个元素都移动一次后方所有元素
 *  
 *  
 */
#include <stdio.h>
#include <string.h>
#include "textbook_def.h"

#include "SqList_lib.h"

Status DeleteK(SqList * a ,int i ,int k );

int main(){
	SqList l1;
	InitList(&l1,10);
	output(&l1);
	DeleteK(&l1, 2, 4);
	output(&l1);
	return 0;
}

Status DeleteK(SqList * a ,int i ,int k ){
	if (i<1 ||k<0|| (i+k)>a->length) return INFEASIBLE;
	//memcpy(&(a->elem[i-1]),&(a->elem[i+k-1]),(k+1)*sizeof(ElemType));
	while ((i+k)<a->length+1){
		a->elem[i-1] = a->elem[i-1+k];
		i++;
	}
	a->length -= k;
	return OK;
	
}
