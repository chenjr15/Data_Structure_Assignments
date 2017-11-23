#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "Queue.h"
#include "LGraph.h"

Status InitGraph(LGraph *g, unsigned num, GraphKind t) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  g->arcnum = 0;
  g->vexnum = num;
  g->kind = t;
  memset(&(g->vertices[0]), 0, sizeof(AdjList));
  return OK;
} //InitGraph
Status BuildGraph(LGraph *g, FILE *f) {
  if (g == NULL)
    return INVALID_ARGUMENT;

  Edge e = {0, 0};
  while (!feof(f)) {

    fscanf(f, "%lc%lc,", &e.v1, &e.v2);

    if (isupper(e.v1) && isupper(e.v2)) {
      e.v1 -= 'A';
      e.v2 -= 'A';
      InsertEdge(g, e);
    }
  }
  return OK;
} //BuildGraph
//tell that whether Edge e existed
Status IsRelated(LGraph *g, Edge e) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p;
  p = g->vertices[e.v1].first;
  int flag = 0;
  while (p) {
    if (p->vexindex == e.v2) {
      flag = 1;
      break;
    }
    p = p->next;
  }
  return flag;
} //IsRelated
Status AddRelation(LGraph *g, int v1_index, int v2_index) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = NULL;
  ArcNode *new = NULL;
  new = malloc(sizeof(ArcNode));
  if (new) {
    new->next = NULL;
    new->vexindex = v2_index;
  }
  p = g->vertices[v1_index].first;
  if (p) {
    while (p->next)
      p = p->next;
    p->next = new;
  } else {
    g->vertices[v1_index].first = new;
  }
  return OK;
} //AddRelation

Status InsertEdge(LGraph *g, Edge e) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  int flag = 0;
  if (!IsRelated(g, e)) {
    AddRelation(g, e.v1, e.v2);
    flag = 1;
  }
  if (!IsRelated(g, (Edge) {
  e.v2, e.v1
})) {
    AddRelation(g, e.v2, e.v1);
    flag = 1;
  }
  (g->arcnum) += flag;
  return OK;
} //InsertEdge
Status SimplePrint(Graph *g) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = NULL;
  printf("V: %d,E: %d\n", g->vexnum, g->arcnum);
  for (int i = 0; i < MAX_VERTEX_NUM; i++) {
    p = g->vertices[i].first;
    if (!p)
      break;
    OUTPUT_VERTIX(i);
    while (p) {
      OUTPUT_VERTIX(p->vexindex);
      p = p->next;
    }
    printf(" |\n");
  }
  return OK;
} //SimplePrint
Status DestoryGraph(LGraph *g) {
  if (g == NULL)
    return INVALID_ARGUMENT;
  ArcNode *p = g->vertices[0].first;
  ArcNode *next = NULL;
  while (p) {
    next = p->next;
    free(p);
    p = next;
  }
  return OK;
} //DestoryGraph
Status DFS(LGraph *g, int start, int *visited, queue *q) {
  if (g == NULL || visited == NULL || q == NULL)
    return INVALID_ARGUMENT;
  if (visited[start])
    return OK;
  visited[start] = 1;
  ArcNode *p = g->vertices[start].first;

  if (!p)
    return ERROR;
  //print nodes here
  OUTPUT_VERTIX(start);
  //add edges into edge set (queue)
  while (p) {
    if (visited[p->vexindex] == 0) {
      InsertEdgeToQueue(q, start, p->vexindex);
    }
    DFS(g, p->vexindex, visited, q);
    p = p->next;
  }
  return OK;
} //DFS

Status BFS(LGraph *g, int start, int *visited, queue *q_edge) {
  if (g == NULL || visited == NULL || q_edge == NULL)
    return INVALID_ARGUMENT;
  ArcNode first = {
    .vexindex = start,
    .next = g->vertices[start].first
  };
  ArcNode *first_p = &first;
  ArcNode *arc_ptr = NULL;
  int RelateCnt[g->vexnum];
  int V_last = -1, V_root = -1;
  queue q_arcnode;
  memset(RelateCnt, 0, sizeof(RelateCnt[0]) * (g->vexnum));
  InitQueue(&q_arcnode, QUEUE_LEN);
  arc_ptr = g->vertices[start].first;
  if (!arc_ptr)
    return ERROR;
  //add first vertix
  EnQueue(&q_arcnode, (SElemType *)&first_p);
  int i = 0, j = 0;
  while (DeQueue(&q_arcnode, (SElemType *)&arc_ptr) == OK) {
    if (visited[arc_ptr->vexindex] == FALSE) {
      if (V_last > -1) {

        if (RelateCnt > 0)
          RelateCnt[i]--;
        InsertEdgeToQueue(q_edge, V_root, arc_ptr->vexindex);
      }
      OUTPUT_VERTIX(arc_ptr->vexindex);
      visited[arc_ptr->vexindex] = TRUE;
    }
    V_last = arc_ptr->vexindex;
    if (RelateCnt[i] == 0 && V_last > -1) {
      V_root = V_last;
      i++;
    }

    arc_ptr = g->vertices[arc_ptr->vexindex].first;
    while (arc_ptr) {

      if (visited[arc_ptr->vexindex] == FALSE) {
        RelateCnt[j]++;
        EnQueue(&q_arcnode, (SElemType *)&arc_ptr);
      }
      arc_ptr = arc_ptr->next;
    }
    j++;
  }
  DestoryQueue(&q_arcnode);
  return OK;
} //BFS
Status InsertEdgeToQueue(queue *Q_EdgePtr, int v1, int v2) {
  Edge *e = NULL;
  e = malloc(sizeof(ArcNode));
  if (!e)
    return ERROR;
  e->v1 = v1;
  e->v2 = v2;
  EnQueue(Q_EdgePtr, (SElemType *)&e);
  return OK;
} //InsertEdgeToQueue
Status PrintEdgeQueue(queue *Q_EdgePtr) {
  Edge *edgeptr = NULL;
  while (DeQueue(Q_EdgePtr, (SElemType *)&edgeptr) == OK) {
    if (!edgeptr)
      continue;
    OUTPUT_EDGE(edgeptr);
    //free the memory of each queue node
    free(edgeptr);
    edgeptr = NULL;
  }
  putchar('\n');
  return 0;
} //PrintEdgeQueue