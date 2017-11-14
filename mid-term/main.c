#include "common.h"
#include "bintree.h"
#include "Queue.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CODE404 0
unsigned CountHight(BinTree* root, ElemType * data);
unsigned OutputDecs(BinTree* root, ElemType * data);
Status Exchange(BinTree* root);
int main(){
  // create binary tree
  BinTree* BT = NULL;
  BT = CreateBT("H");
  BT->R = CreateBT("G");
  BT->R->L = CreateBT("E");
  BT->R->R = CreateBT("F");
  BT->R->R->L = CreateBT("C");
  BT->R->R->L->R = CreateBT("B");
  BT->R->R->R = CreateBT("D");
  char c = 0;
  scanf("%c",&c);
  unsigned h = CountHight(BT,&c);
  printf("'%c' is at level %d\n",c,h);
  if(h == 0)
    printf("NOT FOUND");
  else
    printf("'%c' 's decs is:\n",c);
  OutputDecs(BT,&c);
  putchar('\n');
  Exchange(BT);
  printf("Level traverse after changing:\n");
  LevelTraverse(BT);

  DestoryBT(BT);
  getchar();
  getchar();
  return 0;

}

unsigned CountHight(BinTree* root, ElemType * data){
  //height
  unsigned LevelNo = 0;
  unsigned ThisLevelCount = 0;
  unsigned NextLevelCount = 0;

  if(! root) return CODE404;

  ThisLevelCount = 1 ;
  BinTree* BT = root;
  queue Q;
  InitQueue(&Q,QUEUE_LEN);
 
  while(Q.len || BT ){
    LevelNo++;
    for(unsigned i =0; i<ThisLevelCount;i++){
      if(BT->L){
        EnQueue(&Q,&(BT->L));
        NextLevelCount++;
      }
      if(BT->R){
        EnQueue(&Q,&(BT->R));
        NextLevelCount++;
      }

      if(BT->data == *data){
        return LevelNo;
      }

      if (OK != DeQueue(&Q, &BT))
        BT = NULL;
      }//for
      ThisLevelCount=NextLevelCount;
      NextLevelCount=0;
  }//while
  //Not Found
  DestoryQueue(&Q);
  return CODE404;
}//CountHight

unsigned OutputDecs(BinTree* root, ElemType * data){
  if (!root)
    return CODE404;
  if(!CountHight(root,data)) return CODE404;
  BinTree *bt = root;
  queue q;
  LinerStack s;
  InitStack(&s);
  InitQueue(&q, QUEUE_LEN);
  //push the tree node we find and  nodes before it into stack 
  while (q.len || bt)
  {

    PushStack(&s,bt);
    if (bt->L)
      EnQueue(&q, &(bt->L));
    if (bt->R)
      EnQueue(&q, &(bt->R));
    //found what we want, break 
    if(bt->data == *data)
      break;
    if (OK != DeQueue(&q, &bt))
      bt = NULL;
    }//while 
  LinerStack decs;
  InitStack(&decs);
  BinTree* son;
  BinTree* tempBT=NULL;
  PopStack(&s,&son);
  //find it's father and push into stack 
  while(s.size){
    PopStack(&s,&tempBT);
    if((tempBT->L == son)||(tempBT->R == son) ){
      PushStack(&decs , tempBT);
      son = tempBT;
    }

  }
  ShowStack(&decs,0);
  
  DestoryQueue(&q);
  return decs.size;
}

Status Exchange(BinTree* root){
  if (!root)
    return INVALID_ARGUMENT;
  BinTree *bt = root;
  queue q;
  InitQueue(&q, QUEUE_LEN);
  BinTree* t=NULL;
  while (q.len || bt)
  {

    if(bt->L && bt->R){
      t = bt->L;
      bt->L = bt->R;
      bt->R=t;
    }
    if (bt->L)
      EnQueue(&q, &(bt->L));
    if (bt->R)
      EnQueue(&q, &(bt->R));
    if (OK != DeQueue(&q, &bt))
      bt = NULL;
  }
  DestoryQueue(&q);
  return OK;



}
