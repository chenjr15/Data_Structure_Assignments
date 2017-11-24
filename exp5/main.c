#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LGraph.h"
#include "Queue.h"
int main(void) {
    Graph g;
    int num;
    FILE *f = fopen("edges.txt", "r");
    printf("please input the number of vertex:\n");
    fscanf(f, "%d", &num);
    InitGraph(&g, num, UDG);
    BuildGraph(&g, f);
    fclose(f);
    printf("The graph you input:\n");
    SimplePrint(&g);
    int c = 0;
    int visited[MAX_VERTEX_NUM] = {
        0,
    };
    queue Q_Edge;

    InitQueue(&Q_Edge, QUEUE_LEN);
    while ((c = getchar()) != EOF) {
        if (!isupper(c))
            continue;
        if (!g.vertices[c - 'A'].first) {
            printf("[%c] is not in the graph.\n", c);
            continue;
        }
        memset(visited, 0, sizeof(int) * MAX_VERTEX_NUM);
        /****************Start of DFS****************************/
        //DFS
        printf("DFS:\n");
        DFS(&g, c - 'A', visited, &Q_Edge);
        //print the end of DFS
        printf(" |\n");
        //output the edge set in the queue.
        PrintEdgeQueue(&Q_Edge);
        DestoryQueue(&Q_Edge);
        /***************End of DFS*********************************/
        InitQueue(&Q_Edge, QUEUE_LEN);
        /****************Start of BFS****************************/
        memset(visited, 0, sizeof(int) * MAX_VERTEX_NUM);
        printf("BFS:\n");
        BFS(&g, c - 'A', visited, &Q_Edge);
        printf(" |\n");
        PrintEdgeQueue(&Q_Edge);
        /***************End of DFS*********************************/
    }
    DestoryQueue(&Q_Edge);
    DestoryGraph(&g);
    printf("Done!\nPress Enter to exit.");
    getchar();
    return OK;
}
