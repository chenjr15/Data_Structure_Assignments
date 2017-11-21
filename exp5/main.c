#include <stdio.h>
#include <stdlib.h>
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
  getchar();
  return OK;
}