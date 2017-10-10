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
	//创建带头节点空表
	ha = CreateList();
	hb = CreateList();
	//创建节点并从1-7顺序填入表中
	FillList(ha,lena,1,7);
	FillList(hb,lenb,7,11);
	//打印表
	PrintList("a",ha,lena);
	PrintList("b",hb,lenb);
	//连接两个表，并将连接后的头节点指针存在hc中
	//lena lenb 为对应表长
	hc = linkthem(ha,lena,hb,lenb);
	lenc =lena +lenb;
	//打印hc表
	PrintList("c",hc,lenc);
	//删除hc表，释放空间
	DestoryList(hc);
	return 0;
}

LinkList linkthem(LinkList ha, int lena ,LinkList hb ,int lenb){
	//plong 总是指向较长的表的头节点(若两表相等则指向hb的头节点)
	LinkList  plong ,pshort,hc;
	if(lena > lenb){
		plong= ha ; 
		pshort= hb ;
	}
	else{
		plong = hb;
		pshort = ha;
	}
	//hc总是指向较短的表的头节点
	hc = pshort;
	//遍历pshort至较短的表的尾节点
	while(pshort ->next)
		pshort =pshort ->next;
	//连接两表
	pshort -> next = plong->next;
	return hc;
	
}
