/**
 *  \file 2.15.c
 *  \author ChenJR
 */
#include "textbook_def.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
LinkList linkthem(LinkList ha, int lena ,LinkList hb ,int lenb);

int main(){
	LinkList ha,hb,hc;
	int lena=0,lenb=0,lenc=0;
	ha = CreateList();
	hb = CreateList();
	
	FillList(ha,lena,1,7);
	FillList(hb,lenb,7,11);

	PrintList("a",ha,lena);
	PrintList("b",hb,lenb);

	hc = linkthem(ha,lena,hb,lenb);
	lenc =lena +lenb;
	PrintList("c",hc,lenc);
	
	DestoryList(hc);
}

LinkList linkthem(LinkList ha, int lena ,LinkList hb ,int lenb){
	LinkList  plong ,pshort,hc;
	if(lena > lenb){
		plong= ha ; 
		pshort= hb ;
	}
	else{
		plong = hb;
		pshort = ha;
	}
	hc = pshort;
	while(pshort ->next)
		pshort =pshort ->next;
	pshort -> next = plong->next;
	return hc;
	
}
