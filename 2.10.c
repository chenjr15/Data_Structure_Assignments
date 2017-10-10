#include <stdio.h>
#include <stdlib.h>
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
	while ((i+k)<a->length){
		a->elem[i-1] = a->elem[i-1+k];
		i++;
	}
	a->length -= k;
	return OK;
}
