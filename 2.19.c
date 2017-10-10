/**
 *  \file 2.19.c
 *  \author ChenJR
 *   T(n) = O(n);
 */
#include "textbook_def.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
Status excude(LinkList list, ElemType minK,  ElemType maxK){
	LNode * pMax,*pMin,*t , *p;
	//检查参数
	if (minK>=maxK) return OK;
	if(!LinkList)return INVALID_ARGUMENT;
	pMax=pMin=t=NULL;
	p = list;
	//寻找要删除节点的头
	while(p->next){
		if((p ->next)->data >minK){
			pMin = p;
			break;
		} 
			p = p->next;
	}
	//寻找要删除节点的尾
	while(p->next){
		if((p ->next)->data >=maxK){
			pMax = p;
			break;
		}
		p = p->next;
	}
	if(pMax&&pMin&&(pMax!=pMin)){
		t = pMin->next;
		pMin->next = pMax->next;
		pMax ->next =NULL;
		//释放节点
		DestoryList(t);
	}
	if(pMin && !pMax ){
		DestoryList(pMin->next);
		pMin->next = NULL;
	}
	return OK;
}
int main(){
	LinkList list, p;
	LNode * pMax,*pMin,*t;
	pMax=pMin=t=NULL;
	int len=0;
	//生成新表
	list = CreateList();
	//生成节点并填入递增数列
	FillList(list, len, 0,16);
	PrintList("original list :",list,0);
	excude(list , 5,10);
	PrintList("modified list :",list,0);
}
