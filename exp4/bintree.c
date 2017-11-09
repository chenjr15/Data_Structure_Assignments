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
Status PrintLevelAt(BinTree *root, unsigned int level){
    //parameter checking
    if (!root) return INVALID_ARGUMENT;
    BinTree *bt = root;
    queue q;
    //counters of numbers of nodes
    int Next_Level_Cnt = 0, This_Level_Cnt = 1;
    //level counters
    int level_now = 0, max_level=0;
    InitQueue(&q, QUEUE_LEN);
    while (q.len || bt)
    {
      level_now++;
      for (int i = 0; i < This_Level_Cnt; i++)
      {
        
        if(level == level_now )Visit(bt);
        if (bt->L)
        {
          EnQueue(&q, &(bt->L));
          Next_Level_Cnt++;
        }
        if (bt->R)
        {
          EnQueue(&q, &(bt->R));
          Next_Level_Cnt++;
        }
        if (OK != DeQueue(&q, &bt))
          bt = NULL;
      }

  
      This_Level_Cnt = Next_Level_Cnt;
      Next_Level_Cnt = 0;
    }
    DestoryQueue(&q);
    return OK;
}

/** 
 * @brief  Get max witdth of a binary tree
 * @note   
 * @param  *root: 
 * @param  *width: pointer to save the max width 
 * @param  *level_no: pointer to save the level number with max width
 * @retval 
 */
Status GetMaxWidth(BinTree *root, unsigned int *width, unsigned int *level_no)
{
  //parameter checking
  if (!root) return INVALID_ARGUMENT;
  BinTree *bt = root;
  queue q;
  //counters of numbers of nodes
  int Next_Level_Cnt = 0, This_Level_Cnt = 1, Max_Level_Cnt = 0;
  //level counters
  int level = 0, max_level=0;
  InitQueue(&q, QUEUE_LEN);
  while (q.len || bt)
  {
    level++;
    for (int i = 0; i < This_Level_Cnt; i++)
    {
      
      if (bt->L)
      {
        EnQueue(&q, &(bt->L));
        Next_Level_Cnt++;
      }
      if (bt->R)
      {
        EnQueue(&q, &(bt->R));
        Next_Level_Cnt++;
      }
      if (OK != DeQueue(&q, &bt))
        bt = NULL;
    }
    if (This_Level_Cnt > Max_Level_Cnt)
      max_level = level;
    Max_Level_Cnt = MAX(Max_Level_Cnt, This_Level_Cnt);

    This_Level_Cnt = Next_Level_Cnt;
    Next_Level_Cnt = 0;
  }
  DestoryQueue(&q);
  *width = Max_Level_Cnt;
  *level_no = max_level;
  return OK;
}

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
