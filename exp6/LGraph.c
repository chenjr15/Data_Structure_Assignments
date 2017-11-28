#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "Queue.h"
#include "LGraph.h"

Status InitGraph( LGraph *g, unsigned num, GraphKind t ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    g->arcnum = 0;
    g->vexnum = num;
    g->kind = t;
    memset( &( g->vertices[0] ), 0, sizeof( AdjList ) );
    return OK;
} //InitGraph
Status BuildGraph( LGraph *g, FILE *f ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;

    Edge e = {0, 0};
    while ( !feof( f ) ) {

        fscanf( f, "%lc%lc,", &e.v1, &e.v2 );

        if ( isupper( e.v1 ) && isupper( e.v2 ) ) {
            e.v1 -= 'A';
            e.v2 -= 'A';
            InsertEdge( g, e );
        }
    }
    return OK;
} //BuildGraph
//tell that whether Edge e existed
Status IsRelated( LGraph *g, Edge e ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    ArcNode *p;
    p = g->vertices[e.v1].first;
    int flag = 0;
    while ( p ) {
        if ( p->vexindex == e.v2 ) {
            flag = 1;
            break;
        }
        p = p->next;
    }
    return flag;
} //IsRelated
Status AddRelation( LGraph *g, int v1_index, int v2_index ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    ArcNode *p = NULL;
    ArcNode *new = NULL;
    new = malloc( sizeof( ArcNode ) );
    if ( new ) {
        new->next = NULL;
        new->vexindex = v2_index;
    }
    p = g->vertices[v1_index].first;
    if ( p ) {
        while ( p->next )
            p = p->next;
        p->next = new;
    } else {
        g->vertices[v1_index].first = new;
    }
    return OK;
} //AddRelation

Status InsertEdge( LGraph *g, Edge e ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    int flag = 0;
    if ( !IsRelated( g, e ) ) {
        AddRelation( g, e.v1, e.v2 );
        flag = 1;
    }
    if( ( g->kind == UDG ) || ( g->kind == UDN ) ) {
        if ( !IsRelated( g, ( Edge ) {
        e.v2, e.v1
    } ) ) {
            AddRelation( g, e.v2, e.v1 );
            flag = 1;
        }
    }

    ( g->arcnum ) += flag;
    return OK;
} //InsertEdge
Status SimplePrint( Graph *g ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    ArcNode *p = NULL;
    printf( "V: %d,E: %d\n", g->vexnum, g->arcnum );
    for ( int i = 0; i < MAX_VERTEX_NUM; i++ ) {
        p = g->vertices[i].first;
        if ( !p )
            break;
        OUTPUT_HEAD( i );
        while ( p ) {
            OUTPUT_VERTIX( p->vexindex );
            p = p->next;
        }
        printf( " |\n" );
    }
    return OK;
} //SimplePrint
Status DestoryGraph( LGraph *g ) {
    if ( g == NULL )
        return INVALID_ARGUMENT;
    ArcNode *p = g->vertices[0].first;
    ArcNode *next = NULL;
    while ( p ) {
        next = p->next;
        free( p );
        p = next;
    }
    return OK;
} //DestoryGraph


Status InsertEdgeToQueue( queue *Q_EdgePtr, int v1, int v2 ) {
    Edge *e = NULL;
    e = malloc( sizeof( ArcNode ) );
    if ( !e )
        return ERROR;
    e->v1 = v1;
    e->v2 = v2;
    EnQueue( Q_EdgePtr, ( SElemType * )&e );
    return OK;
} //InsertEdgeToQueue
Status PrintEdgeQueue( queue *Q_EdgePtr ) {
    Edge *edgeptr = NULL;
    while ( DeQueue( Q_EdgePtr, ( SElemType * )&edgeptr ) == OK ) {
        if ( !edgeptr )
            continue;
        OUTPUT_EDGE( edgeptr );
        //free the memory of each queue node
        free( edgeptr );
        edgeptr = NULL;
    }
    putchar( '\n' );
    return 0;
} //PrintEdgeQueue



Status BFS( LGraph *g, int start, int *visited, queue *q_edge ) {
    if ( g == NULL || visited == NULL || q_edge == NULL )
        return INVALID_ARGUMENT;

    ArcNode first = {
        .vexindex = start,
        .next = g->vertices[start].first
    };
    ArcNode *first_p = &first;
    ArcNode *arc_ptr =  g->vertices[start].first;
    if ( !arc_ptr )
        return ERROR;
    /*边标志位*/
    int RelateCnt[MAX_VERTEX_NUM] = {0};

    int V_last = -1, V_root = -1;
    /* 遍历用队列 */
    queue q_arcnode;
    InitQueue( &q_arcnode, QUEUE_LEN );
    //加入第一个顶点
    EnQueue( &q_arcnode, ( SElemType * )&first_p );

    while ( DeQueue( &q_arcnode, ( SElemType * )&arc_ptr ) == OK ) {
        V_root = arc_ptr->vexindex;
        if ( visited[V_root] == FALSE ) {
            OUTPUT_VERTIX( V_root );
            visited[V_root] = TRUE;
        }

        //遍历所有与其相连的顶点
        arc_ptr = g->vertices[V_root].first;
        while ( arc_ptr ) {

            if ( visited[arc_ptr->vexindex] == FALSE ) {
                EnQueue( &q_arcnode, ( SElemType * )&arc_ptr );
                /* (V_last <0)  判断是否第一次进入*/
                if(  ( ( RelateCnt[arc_ptr->vexindex] == FALSE ) ) || ( V_last < 0 )  ) {
                    InsertEdgeToQueue( q_edge, V_root, arc_ptr->vexindex );
                    RelateCnt[arc_ptr->vexindex] = TRUE;
                }
            }
            arc_ptr = arc_ptr->next;
        }// while (arc_ptr) loop for insert related V
        if( V_last >= 0 ) {
            RelateCnt[V_last] = TRUE;
        }

        V_last = V_root;
    }//while (DeQueue())
    DestoryQueue( &q_arcnode );
    return OK;
} //BFS

Status IsPriVertex( ArcNode* path_array, int v_now, int v_tofind ) {

}
Status FindPath( LGraph *g, int src, int dest, int exculede, Edge *paths ) {
    if ( g == NULL || paths == NULL )
        return INVALID_ARGUMENT;
    int visited[MAX_VERTEX_NUM] = {0};
    queue* path_array[20] = {{0},};
    int path_array_index = 0;
    ArcNode first = {
        .vexindex = src,
        .next = g->vertices[src].first
    };
    ArcNode *first_p = &first;
    ArcNode *arc_ptr =  g->vertices[src].first;
    if ( !arc_ptr )
        return ERROR;
    /*边标志位*/
    int RelateCnt[MAX_VERTEX_NUM] = {0};

    int V_last = -1, V_root = -1;
    /* 遍历用队列 */
    queue q_arcnode;
    InitQueue( &q_arcnode, QUEUE_LEN );
    //加入第一个顶点
    EnQueue( &q_arcnode, ( SElemType * )&first_p );

    while ( DeQueue( &q_arcnode, ( SElemType * )&arc_ptr ) == OK ) {
        V_root = arc_ptr->vexindex;
        if ( visited[V_root] == FALSE ) {
            OUTPUT_VERTIX( V_root );
            visited[V_root] = TRUE;
        }

        //遍历所有与其相连的顶点
        arc_ptr = g->vertices[V_root].first;
        queue* path =  malloc( sizeof( queue ) );
        InitQueue( path, MAX_VERTEX_NUM );
        path_array[path_array_index++] = path;
        while ( arc_ptr ) {
            if( !IsPriVertex( path, V_root, arc_ptr->vexindex ) )
                EnQueue( path, &( g->vertices[arc_ptr->vexindex] ) );
            if ( visited[arc_ptr->vexindex] == FALSE ) {
                EnQueue( &q_arcnode, ( SElemType * )&arc_ptr );
                /* (V_last <0)  判断是否第一次进入*/
                if(  ( ( RelateCnt[arc_ptr->vexindex] == FALSE ) ) || ( V_last < 0 )  ) {
                    // InsertEdgeToQueue( q_edge, V_root, arc_ptr->vexindex );
                    RelateCnt[arc_ptr->vexindex] = TRUE;
                }
            }
            arc_ptr = arc_ptr->next;
        }// while (arc_ptr) loop for insert related V
        if( V_last >= 0 ) {
            RelateCnt[V_last] = TRUE;
        }

        V_last = V_root;
    }//while (DeQueue())
    DestoryQueue( &q_arcnode );
    return OK;

}