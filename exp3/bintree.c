#include "common.h"
#include "Stack.h"
#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create
//destory
//pre t
//post t
//in t 
//visit
Status Visit(BinTree * bt) {
  if (!bt) return INVALID_ARGUMENT;
  printf("%c", bt->data);
  return OK;
}

BinTree * CreateBT(ElemType * data) {
  BinTree * bt = (BinTree *)malloc(sizeof(BinTree));
  if (bt) {
    memset(bt, 0, sizeof(BinTree));
    if (data)
      bt->data = *data;
  }
  return bt;

}
Status DestoryBT(BinTree* bt) {
  if (!bt) return INVALID_ARGUMENT;
  return OK;

}

Status PreTraverse_R(BinTree* bt) {
  if (!bt) return INVALID_ARGUMENT;
  Visit(bt);
  if (bt->L)
    PreTraverse_R(bt->L);
  if (bt->R)
    PreTraverse_R(bt->R);
  return OK;
}

Status InTraverse_R(BinTree* bt) {
  if (!bt) return INVALID_ARGUMENT;

  if (bt->L)
    InTraverse_R(bt->L);
  Visit(bt);
  if (bt->R)
    InTraverse_R(bt->R);
  return OK;
}
Status PostTraverse_R(BinTree* bt) {
  if (!bt) return INVALID_ARGUMENT;

  if (bt->L)
    PostTraverse_R(bt->L);

  if (bt->R)
    PostTraverse_R(bt->R);
  Visit(bt);
  return OK;
}

Status PreTraverse(BinTree * bt) {
  if (!bt) return INVALID_ARGUMENT;
  LinerStack S;
  LinerStack* pS = &S;
  InitStack(pS);
 
  while (!isStackEmpty(pS) || bt) {
    /*碰到节点先压栈，然后将指针指向他的左子树，循环直至左子树为空*/
    while (bt) {
    Visit(bt);
      PushStack(pS, bt);
      bt = bt->L;
    }
    /*左子树循环完毕，出栈-取出最后压入的节点，然后再使他指向自己的右子树*/
    if (!isStackEmpty(pS)) {
      PopStack(pS, &bt);
      
      bt = bt->R;
    }
  }
  return OK;
}

Status InTraverse(BinTree * bt) {
  
  if (!bt) return INVALID_ARGUMENT;
  LinerStack S;
  LinerStack* pS = &S;
  InitStack(pS);
 
  while (!isStackEmpty(pS) || bt) {
    /*碰到节点先压栈，然后将指针指向他的左子树，循环直至左子树为空*/
    while (bt) {
      PushStack(pS, bt);
      bt = bt->L;
    }
    /*左子树循环完毕，出栈-取出最后压入的节点，然后再使他指向自己的右子树*/
    if (!isStackEmpty(pS)) {
      PopStack(pS, &bt);
      Visit(bt);
      bt = bt->R;
    }
  }
  return OK;
}

Status PostTraverse(BinTree * bt) {
 if (!bt) return INVALID_ARGUMENT;
  LinerStack S,F;
  LinerStack* pS = &S;
  LinerStack* pF = &F;
  BinTree * father=NULL;
  InitStack(pS);
  InitStack(pF);
 
  while (!isStackEmpty(pS) || bt) {
    /*碰到节点先压栈，然后将指针指向他的左子树，循环直至左子树为空*/
    while (bt) {
      PushStack(pS, bt);
      bt = bt->L;
    }
    /*左子树循环完毕，出栈-取出最后压入的节点，然后再使他指向自己的右子树*/
    if (!isStackEmpty(pS)) {
    	
      PopStack(pS, &bt);
      
      father = bt;
      if (father->L || father->R)
        PushStack(pF, father);
      else
        Visit(bt);
      
      if (!bt->R) {
        //to the end of right
        while (father = GetTop(pF))
        {
          if (father->R != bt) break;
          if (OK == PopStack(pF, &father)) {
            Visit(father);
            bt = father;
          }
            
        }//while
        bt = NULL;

      }//if
      else
      bt = bt->R;
      
      
    }
	
    
  }
  return OK;
}

