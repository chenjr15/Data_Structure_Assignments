#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* 孩子-兄弟法多叉树 存储结构 */
typedef  struct _tree {
    char data;
    struct _tree* son;
    struct _tree* bro;
}*pTree, Tree;

/* 递归先序遍历多叉树 */
Status PreTraverse_R( pTree t ) {
    if( !t ) return INVALID_ARGUMENT;

    /* 访问自身 */
    printf( "%c ", t->data );
    /* 递归访问儿子 */
    if( t->son ) {
        PreTraverse_R( t->son );
    }

    /* 访问兄弟 */
    PreTraverse_R( t->bro );
/*     pTree p = t->bro ;
    while( p ) {
        PreTraverse_R( p );
        p = p->bro;
        
    } */
    return OK;

}

/* 创建节点 */
Tree* CreateTree( ElemType data, Tree* son, Tree* bro ) {
    Tree* pTree = ( Tree* )malloc( sizeof( Tree ) );
    pTree->data = data;
    pTree->son = son;
    pTree->bro = bro;
    return pTree;
}

/* 删除head 的son 或者 bro, 若isbro 非 0 则删除bro 否则删除son */
Status RemoveNode( pTree head, bool isbro ) {
    if( !head ) return INVALID_ARGUMENT;

    /* 被删除的节点 */
    Tree* toDelete = isbro ? head->bro : head->son;
    /* 被删除节点的兄弟 */
    Tree* bros = toDelete->bro;

    Tree* p = NULL ;

    if( isbro ) {
        /* 如果眼删除的是兄弟节点, 则被删除节点的所有儿子提一层,成为被删除节点的兄弟 */
        head->bro = toDelete->son;
        p = head->bro;
        while( p->bro ) {
            p = p->bro;
        }
        /* 在原来儿子后面在加上原来的兄弟 */
        if( toDelete->son )
            p->bro = toDelete->bro;
        else
            head->bro = toDelete->bro;

    } else {
        /* 如果眼删除的是儿子节点, 则被删除节点的所有儿子提一层,成为被删除节点的兄弟 ,head的儿子指针指向新的儿子*/
        head->son = toDelete->son;
        p = head->son;
        while( p->bro ) {
            p = p->bro;
        }
        /* 在原来儿子后面在加上原来的兄弟 */
        if( toDelete->son )
            p->bro = toDelete->bro;
        else
            head->son = toDelete->bro;

    }
    free(toDelete);

    return OK;
}


int main() {
    pTree t = CreateTree( 'A', NULL, NULL );
    t->son = CreateTree( 'B', NULL, NULL );
    t->son->bro = CreateTree( 'C', NULL, NULL );
    t->son->bro->son = CreateTree( 'E', NULL, NULL );
    t->son->bro->son->bro = CreateTree( 'F', NULL, NULL );
    t->son->bro->bro = CreateTree( 'D', NULL, NULL );
    t->son->bro->bro->bro = CreateTree( 'G', NULL, NULL );
    PreTraverse_R( t );
    putchar( '\n' );
    RemoveNode( t->son, TRUE );
    PreTraverse_R( t );
    putchar( '\n' );
    return OK;
}