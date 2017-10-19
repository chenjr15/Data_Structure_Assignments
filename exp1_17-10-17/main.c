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
    printf("input first m and n\n");
    scanf("%d %d",&m,&n);
    for(i =0;i<n;i++){
        printf("please input pwd of ManType %d \n",i+1);
        scanf("%d",&password);

        newNode = CreateNode((ManType){i,password},head);

        if(i == 0){
            newNode->next =newNode;
            head = newNode;
            }
        else
            InsertNode(pNode,newNode);
        pNode = newNode;
    }
    //OutputList(head);
    pNode=head;
    while(head){
    	for(i=0;i<m-1;i++)
    		pNode = pNode->next;
    	LuckyNode=pNode;
		while(pNode->next!=LuckyNode)
			pNode = pNode->next;
		preNode = pNode;
        pNode =pNode->next;
        m = pNode->man.password;
        n = pNode->man.number;
        nextNode = pNode->next;
        printf("n = %d  m = %d \n",n+1,m);
        if(pNode->next == pNode){
        	//仅剩一个节点，直接释放节点并
            free(pNode);
            pNode=NULL;
            head=NULL; 
        }else{
            //剩余 
            RemoveNode(preNode);
            pNode = nextNode;
            //OutputList(pNode);
            //printf("--------------\n");
        }

    }

    return 0;
}
