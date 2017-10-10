/**
 *  \file 2.19.c
 *  \author ChenJR
 */
#include "textbook_def.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#define minK -1
#define maxK 20
int main(){
	
	LinkList list, p;
	LNode * pMax,*pMin,*t;
	pMax=pMin=t=NULL;
	int len=0;
	list = CreateList();
	FillList(list, len, 0,16);
	
	PrintList("original list :",list,0);
	p = list;
	while(p->next){
		if((p ->next)->data >minK){
			pMin = p;
			
			break;
		}
			p = p->next;
	}
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
		DestoryList(t);
	}
	if(pMin && !pMax ){
		DestoryList(pMin->next);
		pMin->next = NULL;
	}
	

	PrintList("modified list :",list,0);
	
}
