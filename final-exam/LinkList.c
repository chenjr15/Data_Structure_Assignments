#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* 单向链表定义 */
typedef struct _linklist {
    ElemType data;
    struct _linklist * next;
}*List, Node;

/* 创建节点 */
Node* CreateNode( ElemType data, Node* next ) {
    Node* pNode = ( Node* )malloc( sizeof( Node ) );
    pNode->data = data;
    pNode->next = next;
    return pNode;
}

/* 删除链表, 释放内存.
   不释放头结点
 */
Status DestoryList( List list ) {
    if ( !list ) return INVALID_ARGUMENT;
    List p = list->next;
    List t;
    while( p ) {
        t = p;
        p = p->next;
        free( t );
    }
    return OK;
}
/* 在nowNode 后面插入新节点newNode */
Status InsertNode( Node* nowNode, Node* newNode ) {
    if( ( !nowNode ) || ( !newNode ) ) return INVALID_ARGUMENT;
    newNode->next = nowNode->next;
    nowNode->next = newNode;
    return OK;
}



/* 删除pre->next指向的节点 */
Status RemoveNode( Node * pre ) {
    if( ( pre == NULL ) || ( pre->next == NULL ) )return INVALID_ARGUMENT;
    Node* t = pre->next;
    pre->next = t->next;
    free( t );
    return OK;
}
/* 转置链表 l, 用头插法 */
List ReversList( List l ) {
    if( !l->next ) return OK;
    Node* oldHead = l;
    Node* newHead = CreateNode( 0, NULL );
    Node* p = oldHead->next;
    Node * t;
    /* 只要p非空就一直往后走,直到链尾 */
    while( p ) {
        t = p->next;
        InsertNode( newHead, p );
        p = t;
    }
    return newHead;
}


/* 从文件构建链表 */
Status BuildFromFile( char* filename, List l ) {
    if( !filename ) {
        printf( "空文件名!\n" );
        return INVALID_ARGUMENT;
    }
    if ( ! l ) {
        printf( "头节点为空!\n" );
        return INVALID_ARGUMENT;
    }
    int total = 0;
    ElemType data;
    Node* p = l;
    FILE* f = fopen( filename, "r" );
    fscanf( f, "%d", &total );
    for( ; total > 0; total-- ) {
        fscanf( f, "%d", &data );
        InsertNode( p, CreateNode( data, NULL ) );
        p = p->next;
    }
    return OK;
}

/* 输出链表 */
void ShowList( List l ) {
    if( !l ) return;
    Node* p = l->next;
    /* 只要p非空就一直往后走,直到链尾 p 为空 */
    while( p ) {
        printf( "%d, ", p->data );
        p = p->next;
    }
    putchar( '\n' );
    return;
}

int main( void ) {
    /* 创建头结点 */
    List h = CreateNode( 0, NULL );
    /* 从文件 linklist.txt 构建链表, 第一行为个数,第二行开始为节点的值*/
    BuildFromFile( "linklist.txt", h );
    ShowList( h );
    List new = ReversList( h );
    //ShowList( h );
    ShowList(new);
    return OK;
}