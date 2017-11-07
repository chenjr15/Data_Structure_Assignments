/**
 *  \file 2.20.c
 *  \author ChenJR
 *  	T(n) = O(n)?
 */
#include "textbook_def.h"
#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
Status UniqueNode(LinkList);
int main(){
	LinkList list,rear;
	int len=0;
	list = CreateList();
	//create repeating nodes 
	rear = list;
	for(int i = 1; i<14;i++){ 
			len+= 1;
			rear->next= CreateNode(i/3,NULL); 
			rear = rear->next; 
		} 
	PrintList("original list ",list,len);
	UniqueNode(list);
	PrintList("modified list ",list,-1);
}
Status UniqueNode(LinkList h){
	LinkList  p,pnext,t;
	p = h->next;
	pnext  = p->next;
	while(p && pnext){
		//若当前节点数据与下一节点相同则删除下一节点
		if (p->data == pnext->data){
			p->next = pnext ->next;
			t = pnext;
			pnext = p->next;
			//释放内存
			free(t);
		}else{
		//数据不相等，则指针往后挪
			p=pnext;
			pnext = p->next;
		}
	}
}
