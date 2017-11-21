#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
#define GetIndex(x,y) (((x)-'A')*((x)-'A'+1)/2+((y)-'A'))

typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef int VRType;
typedef struct arccell{
  VRType weight;


}ArcCell;
typedef struct {
  ArcCell* arcs;
  int vexnum,arcnum;
  GraphKind kind; 

} MGraph;

Status InsertE(MGraph *g, FILE *f);
Status BuildGraph(MGraph *g,FILE* f);
Status InitGraph(MGraph *g, unsigned num, GraphKind t);