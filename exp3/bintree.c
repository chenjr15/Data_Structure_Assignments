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

  return OK;
}

Status InTraverse(BinTree * bt) {
  
  if (!bt) return INVALID_ARGUMENT;
  LinerStack S;
  LinerStack* pS = &S;
  InitStack(pS);
 
  while (!isStackEmpty(pS) || bt) {
    /*�����ڵ���ѹջ��Ȼ��ָ��ָ��������������ѭ��ֱ��������Ϊ��*/
    while (bt) {
      PushStack(pS, bt);
      bt = bt->L;
    }
    /*������ѭ����ϣ���ջ-ȡ�����ѹ��Ľڵ㣬Ȼ����ʹ��ָ���Լ���������*/
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
  return OK;
}

