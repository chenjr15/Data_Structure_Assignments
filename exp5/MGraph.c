#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MGraph.h"
Status InitGraph(MGraph *g, unsigned num, GraphKind t)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  g->arcnum = 0;
  g->vexnum = num;
  if (num){
    g->arcs = (ArcCell *)malloc(sizeof(ArcCell) * num);
    memset(g->arcs, 0,sizeof(ArcCell) * num);
    }
  else
    g->arcs = NULL;
  g->kind = t;
  return OK;
}
Status BuildGraph(MGraph *g, FILE *f)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  int num = g->vexnum;
  while (!feof(f))
  {
    InsertE(g, f);
  }
  return OK;
}

Status InsertE(MGraph *g, FILE *f)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  char a, b;
  fscanf(f, "%c%c,", &a, &b);
  if (isupper(a) && isupper(b))
  {
    if (a > b)
      *(g->arcs + GetIndex(a,b)) = (ArcCell){
          .weight = 1,
      };
    else
      *(g->arcs +GetIndex(b,a)) = (ArcCell){
          .weight = 1,
      };
    g->arcnum++;
  }
  return OK;
}
