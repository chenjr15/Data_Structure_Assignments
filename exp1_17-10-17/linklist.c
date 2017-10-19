/**
 *  \file linklist.c
 *  \author ChenJR
 */
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
void OutputList(LinkList l){
    LinkList head = l;
    if(l == NULL) return;
	do{
        printf("n = %d ,pwd = %d\n",l->man.number+1,l->man.password);
		l=l->next;

	}while (l!=head);
	putchar('\n');

}

LNode* CreateNode(ManType man, LNode* next){
	LNode* pNode = (LNode*)malloc(sizeof(LNode));
	pNode->man = man;
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
/*insert node new into list after node now*/
Status InsertNode(LNode* nowNode,LNode* newNode){
    newNode->next = nowNode->next;
    nowNode->next = newNode;
    return OK;
}
/*remove node after pre*/
Status RemoveNode(LNode * pre){
    if((pre ==NULL )||(pre->next==NULL))return ERROR;
    LNode* t = pre->next;
    pre->next = t->next;
    free(t);
    return OK;
}
