#include <stdio.h>
#include <stdlib.h>
#include "common.h"


Status InsertSort( SqList * list ) {
    //list->r[0] = list->r[1];
    if( !list ) return INVALID_ARGUMENT;
    for( int i = 2 ; i <= list->length; ++i ) {
        if ( list->r[i].key < list->r[i - 1].key ) {
            list->r[0] = list->r[i];
            list->r[i] = list->r[i - 1];
            int j ;
            for( j = i - 2; list->r[0].key < list->r[j].key; --j ) {
                list->r[j + 1] = list->r[j];
            }//for( int j = i - 2; list->r[0].key < list->r[j].key; j-- )

            list->r[j + 1] = list->r[0];

        }//if ( list->r[i].key < list->r[i - 1].key )

    }//for
    return OK;
}//InsertSort()

Status SelectionSort( SqList * list ) {
    if( !list ) return INVALID_ARGUMENT;
    int min=1;
    for ( int i = 1; i <= list->length; i++ ) {
        /* 寻找最小值 索引*/
        min = i;
        for( int j = i; j <= list->length; j++ ) {
            if( list->r[j].key < list->r[min].key )
                min = j;

        }//for(int j = i;j<list->length;j++)
        list->r[0] = list->r[min];
        list->r[min] = list->r[i];
        list->r[i] = list->r[0] ;
    }//for(i)

    return OK;
}//SelectionSort( SqList * list )