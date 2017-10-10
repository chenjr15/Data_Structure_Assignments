/**
 *  \file linklist.c
 *  \author ChenJR
 */
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
void OutputList(LinkList l){
	while (l->next){
		l=l->next;
		printf("%d ",l->data);
	}
	putchar('\n');
	
}

LNode* CreateNode(ElemType data, LNode* next){
	LNode* pNode = (LNode*)malloc(sizeof(LNode));
	pNode->data = data;
	pNode->next = next;
	return pNode;
	
}
Status DestoryList(LinkList list){
	LinkList p = list;
	LinkList t;
	while(p){
		t = p;
		p= p->next;
		free(t);
	}
	return OK;
}
