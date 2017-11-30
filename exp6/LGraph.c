#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "Queue.h"
#include "LGraph.h"

void OutputQueue( queue *D ) {
    int i;
    for ( i = 0; i < D->len; i++ ) {
        OUTPUT_VERTEX( GET( D, i ) );
    }
    //putchar( '\n' );
    // printf( "len:%d", D->len );
    // putchar( '\n' );
} //OutputQueue

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
            continue;
        OUTPUT_HEAD( i );
        while ( p ) {
            OUTPUT_VERTEX( p->vexindex );
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


Status FindPath( LGraph *g, int src, int dest, int exculede, int  *visited, queue* Q ) {
    if ( g == NULL || visited == NULL )
        return INVALID_ARGUMENT;
    int temp;
    visited[src] = TRUE;
    EnQueue( Q, &src );
    ArcNode* ptr_edges = g->vertices[src].first;

    while( ptr_edges ) {
        if( ( visited[ptr_edges->vexindex] ) ||  ( ptr_edges->vexindex == exculede ) ) {
            ptr_edges = ptr_edges->next;
            continue;
        }
        if( ptr_edges->vexindex == dest ) {

            OutputQueue( Q );
            OUTPUT_VERTEX_PLAIN( dest );
            putchar( '\n' );
            //break;
        }


        FindPath( g, ptr_edges->vexindex, dest, exculede, visited, Q );
        //DeQueue( Q, &temp );
        ptr_edges = ptr_edges->next;

    }

    visited[src] = 0;
    DeQueueR( Q, &temp );
    if( ptr_edges )
        return OK;
    else {

        // visited[src] = 0;
        return ERROR;
    }

}