#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "Queue.h"
#include "LGraph.h"

Status InitGraph(LGraph *g, unsigned num, GraphKind t)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  g->arcnum = 0;
  g->vexnum = num;
  g->kind = t;
  memset(&(g->vertices[0]), 0, sizeof(AdjList));
  return OK;
}
Status BuildGraph(LGraph *g, FILE *f)
{
  if (g == NULL)
    return INVALID_ARGUMENT;

  Edge e = {0, 0};
  while (!feof(f))
  {

    fscanf(f, "%c%c,", &e.v1, &e.v2);

    if (isupper(e.v1) && isupper(e.v2))
    {
      e.v1 -= 'A';
      e.v2 -= 'A';
      InsertEdge(g, e);
    }
  }
  return OK;
}
//tell that whether Edge e existed
Status IsRelated(LGraph *g, Edge e)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p;
  p = g->vertices[e.v1].first;
  int flag = 0;
  while (p)
  {
    if (p->vexindex == e.v2)
    {
      flag = 1;
      break;
    }
    p = p->next;
  }
  return flag;
}
Status AddRelation(LGraph *g, int v1_index, int v2_index)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = NULL;
  ArcNode *new = NULL;
  new = malloc(sizeof(ArcNode));
  if (new)
  {
    new->next = NULL;
    new->vexindex = v2_index;
  }
  p = g->vertices[v1_index].first;
  if (p)
  {
    while (p->next)
      p = p->next;
    p->next = new;
  }
  else
  {
    g->vertices[v1_index].first = new;
  }
  return OK;
}

Status InsertEdge(LGraph *g, Edge e)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  int flag = 0;
  if (!IsRelated(g, e))
  {
    AddRelation(g, e.v1, e.v2);
    flag = 1;
  }
  if (!IsRelated(g, (Edge){e.v2, e.v1}))
  {
    AddRelation(g, e.v2, e.v1);
    flag = 1;
  }
  (g->arcnum) += flag;
  return OK;
}
Status SimplePrint(Graph *g)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = NULL;
  printf("V: %d,E: %d\n", g->vexnum, g->arcnum);
  for (int i = 0; i < MAX_VERTEX_NUM; i++)
  {
    p = g->vertices[i].first;
    if (!p)
      break;
    printf("[%c]->", i + 'A');
    while (p)
    {
      printf("%c->", p->vexindex + 'A');
      p = p->next;
    }
    printf(" |\n");
  }
  return OK;
}
Status DestoryGraph(LGraph *g)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = g->vertices[0].first;
  ArcNode *next = NULL;
  while (p)
  {
    next = p->next;
    free(p);
    p = next;
  }
  return OK;
}
Status DFS(LGraph *g, int start, int *visited, queue *q)
{
  if (g == NULL)
    return INVALID_ARGUMENT;
  if (visited[start])
    return OK;
  visited[start] = 1;
  ArcNode *p = g->vertices[start].first;
  Edge *e = NULL;
  if (!p)
    return ERROR;
  
  printf("[%c]->", start + 'A');
  while (p)
  {
    if (visited[p->vexindex] == 0)
  {
    e = malloc(sizeof(ArcNode));
    if (e)
    {
      e->v1 = start;
      e->v2 = p->vexindex;
      EnQueue(q, &e);
    }
    else
      printf("malloc failed!\n");
  }
    DFS(g, p->vexindex, visited, q);
    p = p->next;
  }
  return OK;
}