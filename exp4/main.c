#include "Stack.h"
#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  BinTree * bt,*root;
  BinTree *l, *r;
  ElemType c;
  root = CreateBT("-");
  bt = root;
  root->L = CreateBT("+");
  root->R = CreateBT("/");
  root->L->L = CreateBT("a");
  root->L->R = CreateBT("*");
  root->L->R->L = CreateBT("b");
  root->L->R->R = CreateBT("-");
  root->L->R->R->L = CreateBT("c");
  root->L->R->R->R = CreateBT("d");
  root->R->L = CreateBT("e");
  root->R->R = CreateBT("f");

  LevelTraverse(bt);
  putchar('\n');
  unsigned int w =0,maxno =0;
  GetMaxWidth(bt,&w,&maxno);
  printf("Max width is %u, at level %u \n",w,maxno);
  PrintLevelAt(bt,maxno);
  DestoryBT(bt);
  getchar();
  return OK;
}