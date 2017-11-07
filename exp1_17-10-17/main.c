#include <stdio.h>
#include <stdlib.h>
#include "textbook_def.h"
#include "linklist.h"
int main()
{
    LinkList head,pNode,newNode,preNode,nextNode,LuckyNode;
    int m,n;
    int password;
    int i;
	//输入m 和 n
    printf("input first m and n\n");
    scanf("%d %d",&m,&n);
	//输入密码并构造链表
    for(i =0;i<n;i++){
        printf("please input pwd of man %d \n",i+1);
        scanf("%d",&password);
		//将输入的密码和当前序号存入新节点，并将新节点的next指针指向第一个节点
        newNode = CreateNode((ManType){i,password},head);
		//若是第一个节点，则将新节点的next指向自身，并让head指向当前节点
		//否则在当前结点后插入新节点
        if(i == 0){
            newNode->next =newNode;
            head = newNode;
            }
        else
            InsertNode(pNode,newNode);
		//使当前节点指针指向新节点
        pNode = newNode;
    }
    //OutputList(head);
    pNode=head;
    while(head){
		//找到密码值为m的节点
    	for(i=0;i<m-1;i++)
    		pNode = pNode->next;
    	LuckyNode=pNode;
		//找到LuckyNode的头前驱
		while(pNode->next!=LuckyNode)
			pNode = pNode->next;
		preNode = pNode;
        pNode =pNode->next;
		//取出密码和序号
        m = pNode->man.password;
        n = pNode->man.number;
        nextNode = pNode->next;
		//打印数据
        printf("n = %d  m = %d \n",n+1,m);
        if(pNode->next == pNode){
        	//仅剩一个节点，直接释放节点并
            free(pNode);
            pNode=NULL;
            head=NULL; 
        }else{
            //剩余多个节点，直接通过前驱删除当前结点，并让pNode指向下一节点
            RemoveNode(preNode);
            pNode = nextNode;
            //OutputList(pNode);
            //printf("--------------\n");
        }

    }

    return 0;
}
