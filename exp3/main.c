#include "common.h"
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

  PreTraverse_R(bt);
  putchar('\n');
  InTraverse_R(bt);
  putchar('\n');
  PostTraverse_R(bt);
  putchar('\n');
  InTraverse(bt);
  return OK;
}