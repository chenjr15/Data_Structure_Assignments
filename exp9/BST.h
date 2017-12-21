#ifndef __BST_H__
#define __BST_H__
#include "common.h"
#include "bintree.h"

BinTree* InsertElem( BinTree* bt, ElemType* elem_p );
BinTree* BuildBST( ElemType* elemlist, int len );
Status IsBST( BinTree* bt ) ;

#endif // !__BST_H__