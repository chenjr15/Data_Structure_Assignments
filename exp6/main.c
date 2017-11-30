#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LGraph.h"
#include "Queue.h"
int main( void ) {
    Graph g;
    int num;
    FILE *f = fopen( "edges.txt", "r" );
    printf( "please input the number of vertex:\n" );
    fscanf( f, "%d", &num );
    InitGraph( &g, num, UDG );
    BuildGraph( &g, f );
    fclose( f );
    printf( "The graph you input:\n" );
    SimplePrint( &g );
    int c = 0;
    int visited[MAX_VERTEX_NUM] = {
        0
    };
    memset(visited,0,sizeof(int)*MAX_VERTEX_NUM);
    queue*  Q = malloc( sizeof( queue ) );
    InitQueue( Q, QUEUE_LEN );
    FindPath( &g, 'L' - 'A', 'I' - 'A', 'K' - 'A', visited,Q );
    DestoryQueue( Q );
    DestoryGraph( &g );
    printf( "Done!\nPress Enter to exit." );
   // getchar();
    return OK;
}
