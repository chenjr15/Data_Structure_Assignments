#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "sort.h"

Status AddElem( SqList *l, RedType *record ) {
    if( l->length >= MAXSIZE ) return OVERFLOW;
    l->r[l->length + 1] = *record;
    l->length++;
    return OK;
}//Status AddElem( SqList *l, RedType *record )
void ShowList( SqList*l ) {
    if( l->length >= MAXSIZE ) return;
    printf( "H:%d | ", l->r[0].key );
    for( int i = 1; i <= l->length; i++ ) {
        printf( "%d ", l->r[i].key );
    }
    putchar( '\n' );
}//void ShowList( SqList*l )

int main() {
    SqList *l = malloc( sizeof( SqList ) );
    memset( l, 0, sizeof( SqList ) );
    time_t t;

    RedType r ;
    srand((unsigned int)(time(NULL)));
    for( int i = 0 ; i < 10; i++ ) {
        r.key = rand() % 10;
        AddElem( l,  &r );
    }
    printf( "原顺序表:\n" );
    ShowList( l );
    InsertSort( l );
    printf( "直接插入排序后的顺序表:\n" );
    ShowList( l );

    /* 清空表 */
    memset( l, 0, sizeof( SqList ) );
    //srand((unsigned int)(time(NULL)));
    for( int i = 0 ; i < 10; i++ ) {
        r.key = rand() % 10;
        AddElem( l,  &r );
    }
    printf( "原顺序表:\n" );
    ShowList( l );
    SelectionSort( l );
    printf( "选择排序后的顺序表:\n" );
    ShowList( l );
    getchar();
    return OK;
}