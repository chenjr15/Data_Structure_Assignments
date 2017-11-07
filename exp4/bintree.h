#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__
#include "common.h"

Status Visit(BinTree * bt);
BinTree * CreateBT(ElemType * data);
Status DestoryBT(BinTree* bt);
Status PreTraverse_R(BinTree* bt);
Status InTraverse_R(BinTree* bt);
Status PostTraverse_R(BinTree* bt);

Status PreTraverse(BinTree* bt);
Status InTraverse(BinTree* bt);
Status PostTraverse(BinTree* bt);

Status LevelTraverse(BinTree * bt);
Status GetMaxWidth(BinTree *root, unsigned int *width,unsigned int *level_no);
Status PrintLevelAt(BinTree *root, unsigned int level);
#endif // !__BIN_TREE_H__
