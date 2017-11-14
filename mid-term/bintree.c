#include "common.h"
#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
/** 
 * @brief  Print nodes at level [level]
 * @note   
 * @param  *root: root pointer of binary tree
 * @param  level: level number
 * @retval 
 */


Status LevelTraverse(BinTree *root)
{
  if (!root)
    return INVALID_ARGUMENT;
  BinTree *bt = root;
  queue q;
  InitQueue(&q, QUEUE_LEN);
  while (q.len || bt)
  {

    Visit(bt);
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

Status Visit(BinTree *bt)
{
  if (!bt)
    return INVALID_ARGUMENT;
  printf("%c", bt->data);
  return OK;
}

BinTree *CreateBT(ElemType *data)
{
  BinTree *bt = (BinTree *)malloc(sizeof(BinTree));
  if (bt)
  {
    memset(bt, 0, sizeof(BinTree));
    if (data)
      bt->data = *data;
  }

  return bt;
}
Status DestoryBT(BinTree *bt)
{
  if (!bt)
    return INVALID_ARGUMENT;
  if (bt->L)
    DestoryBT(bt->L);

  if (bt->R)
    DestoryBT(bt->R);
  free(bt);
  return OK;
}

// BinTree *MakeBT(const char * str){
//   char *pchar = str;
//   char c;
//   BinTree* root = 
//   while((c = *pchar++)){
    
//   }

// }

Status PreTraverse_R(BinTree *bt)
{
  if (!bt)
    return INVALID_ARGUMENT;
  Visit(bt);
  if (bt->L)
    PreTraverse_R(bt->L);
  if (bt->R)
    PreTraverse_R(bt->R);
  return OK;
}

Status InTraverse_R(BinTree *bt)
{
  if (!bt)
    return INVALID_ARGUMENT;

  if (bt->L)
    InTraverse_R(bt->L);
  Visit(bt);
  if (bt->R)
    InTraverse_R(bt->R);
  return OK;
}
Status PostTraverse_R(BinTree *bt)
{
  if (!bt)
    return INVALID_ARGUMENT;

  if (bt->L)
    PostTraverse_R(bt->L);

  if (bt->R)
    PostTraverse_R(bt->R);
  Visit(bt);
  return OK;
}
