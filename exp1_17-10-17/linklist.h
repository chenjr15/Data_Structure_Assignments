/**
 *  \file linklist.h
 *  \author ChenJR
 */
#ifndef __LINKLIST_H__
#define __LINKLIST_H__



#include "textbook_def.h"


#define CreateList() CreateNode(0,NULL)

#define FillList(head,len,start,end) \
	do{ \
		LNode *rear =(LNode*) head; \
		for(int i = start; i<end;i++){ \
			len+= 1;\
			rear->next= CreateNode(i,NULL); \
			rear = rear->next; \
		} \
	}while(0)

#define PrintList(name, head ,len)\
	do { \
		printf("%s (%d):",name,len); \
		OutputList(head); \
	}while(0)

void  OutputList(LinkList l);
Status DestoryList(LinkList list);
LNode* CreateNode(ManType man, LNode* next);
Status InsertNode(LNode* nowNode,LNode* newNode);
Status RemoveNode(LNode * pre);



#endif
