#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 26

typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef int VRType;

typedef struct arcnode{
  //vertix index
  int vexindex;
  struct arcnode * next;
}ArcNode;
typedef struct  vnode{
  ArcNode* first;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
  AdjList vertices;
  int vexnum,arcnum;
  int kind;
}LGraph;

// typedef struct edge{
//   int v1,v2;
// }Edge;

typedef LGraph Graph;
#define OUTPUT_VERTIX(ch) printf("["FONT_COLOR"%c"NONE"]->", (ch) + 'A')

Status InsertEdge(LGraph *g, Edge e);
Status AddRelation(LGraph *g, int v1_index, int v2_index);
Status IsRelated(LGraph *g, Edge e);
Status BuildGraph(LGraph *g, FILE *f);
Status InitGraph(LGraph *g, unsigned num, GraphKind t);
Status SimplePrint(Graph* g);
Status DestoryGraph(LGraph* g );
Status DFS(LGraph * g,int start,int* visited,queue* q);
Status BFS(LGraph *g, int start, int *visited, queue *q_edge);