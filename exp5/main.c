#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LGraph.h"

int main(void)
{
  Graph g;
  int num;
  FILE *f = fopen("edges.txt","r");
  printf("please input the number of vertex:\n");
  fscanf(f, "%d", &num);
  InitGraph(&g, num, UDG);
  BuildGraph(&g, f);
  fclose(f);
  SimplePrint(&g);
  int c = 0;
  int  visited[MAX_VERTEX_NUM]={0,};
  while((c = getchar())!=EOF){
    if (isupper(c)){
      memset(visited,0,sizeof(int)*MAX_VERTEX_NUM);
      if(DFS(&g,c-'A',visited)==OK)
        printf(" |\n");
      else
        printf("[%c] is not in the graph.\n",c);
    }
     
  }
  DestoryGraph(&g);
  printf("Done!\nPress Enter to exit.");
  getchar();
  return OK;
}
