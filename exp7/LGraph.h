#pragma once
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 26

typedef enum { DG,
               DN,
               UDG,
               UDN
             } GraphKind;
typedef int VRType;

typedef struct arcnode {
    //vertEX index
    int vexindex;
    int len;
    struct arcnode *next;
} ArcNode;
typedef struct vnode {
    ArcNode *first;
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
} LGraph;

// typedef struct edge{
//   int v1,v2;
// }Edge;

typedef LGraph Graph;


Status InsertEdge( LGraph *g, Edge e );
Status AddRelation( LGraph *g, int v1_index, int v2_index );
Status IsRelated( LGraph *g, Edge e );
Status BuildGraph( LGraph *g, FILE *f );
Status InitGraph( LGraph *g, unsigned num, GraphKind t );
Status SimplePrint( Graph *g );
Status DestoryGraph( LGraph *g );
// Status DFS( LGraph *g, int start, int *visited, queue *q );
// Status BFS( LGraph *g, int start, int *visited, queue *q_edge );
Status PrintEdgeQueue( queue *Q_EdgePtr );
Status InsertEdgeToQueue( queue *Q_EdgePtr, int v1, int v2 );
Status FindPath( LGraph *g, int src, int dest, int exculede, int  *visited, queue* Q ) ;

//
#ifdef COLORTEXT
#define OUTPUT_VERTEX(ch) printf("[" FONT_COLOR "%d" NONE "]->", (ch)  )
#define OUTPUT_VERTEX(ch) printf("[" FONT_COLOR "%d" NONE "]-" FONT_COLOR "%d" NONE ">", (ch)  )
#define OUTPUT_EDGE(edgeptr) printf("(" FONT_COLOR "%d" NONE "," FONT_COLOR "%d" NONE "), ", \
                                      (edgeptr)->v1, (edgeptr)->v2);
#define OUTPUT_HEAD(ch) printf( HEAD_COLOR " [%d]->" NONE, (ch) +)
#define OUTPUT_VERTEX_PLAIN(ch) printf("[" HEAD_COLOR "%d" NONE "]", (ch) + )
#else
#define OUTPUT_EDGE(edgeptr) printf("(%d,%d), ", edgeptr->v1  , edgeptr->v2  );
#define OUTPUT_VERTEX(ch) printf("[%d]->", (ch)  )
#define OUTPUT_VERTEX_WEIGHTED(ch,len) printf("[%d]-%d>", (ch),(len)  )
#define OUTPUT_VERTEX_PLAIN(ch) printf("[%d]", (ch)  )
#define OUTPUT_HEAD(ch) printf( " [ %d ] -> " , (ch)  )
#endif
