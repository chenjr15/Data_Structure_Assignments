

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
struct _table {
    ElemType* elem;
    unsigned len;

};
typedef struct _table table;
typedef struct _table*  table_ptr;
int BinSearch( table_ptr t, ElemType tofind );
int BinSearchR( table_ptr t, ElemType tofind );
int BinSearchR_( table_ptr t, ElemType tofind, int L, int R );
int main( int argc, char* argv[] ) {

    /*获取文件名*/
    char  filename[50];
    if ( argc > 1 ) {
        strncpy( filename, argv [ 1], 49 );

    } else {
        printf( "Please input filename\n" );
        scanf( "%49s", &filename );
    }
    /*创建表*/
    table t;
    /*从文件中读取数据用于构建表*/
    FILE* f = fopen( filename, "r" );
    fscanf( f, "%d", &t.len );
    t.elem = malloc( ( t.len ) * sizeof( ElemType ) );
    for( int i = 0; i < t.len; i++ ) {
        fscanf( f, "%d", &( t.elem[i] ) );
    }
    fclose( f );
    /*获取查找值*/
    int tosearch;
    int place;
    printf( "please input a number to search:" );
    scanf( "%d", &tosearch );
    printf( "Result by iteration:\n" );
    place = BinSearchR( &t, tosearch );
    if ( place < 0 ) {
        printf( "404 Not Found!\n" );
    } else {
        printf( "%d is at place %d\n", tosearch, place );
    }
    printf( "Result by recurtion::\n" );
    place = BinSearch( &t, tosearch );
    if ( place < 0 ) {
        printf( "404 Not Found!\n" );
    } else {
        printf( "%d is at place %d\n", tosearch, place );
    }
    return OK;
}
/** 
 * @brief  迭代法求二分查找
 * @note   
 * @param  t: 
 * @param  tofind: 
 * @retval 
 */
int BinSearch( table_ptr t, ElemType tofind ) {
    int index = -1;
    int L, R, M;
    L = 0;
    R = t->len - 1;
    M = ( L + R ) / 2;
    while( ( L < R ) && L != R ) {
        if( t->elem[M] == tofind ) {
            index = M;
            L = R;
        } else if( t->elem[M] < tofind ) {
            L = M + 1;
        } else {
            R = M - 1;
        }
        M = ( L + R ) / 2;
    }
    return index;
}
/** 递归主体
 * @brief  
 * @note   
 * @param  t: 
 * @param  tofind: 
 * @param  L: 
 * @param  R: 
 * @retval 
 */
int BinSearchR_( table_ptr t, ElemType tofind, int L, int R ) {
    int index = -1;
    int  M = ( L + R ) / 2;
    if ( L > R ) return -1;
    if( t->elem[M] == tofind ) {
        return M;
    } else if( t->elem[M] < tofind ) {
        L = M + 1;
    } else {
        R = M - 1;
    }
    index = BinSearchR_( t, tofind, L, R );

    return index;
}
/** 
 * @brief  递归算法外层
 * @note   
 * @param  t: 
 * @param  tofind: 
 * @retval 
 */
int BinSearchR( table_ptr t, ElemType tofind ) {

    int L, R;
    L = 0;
    R = t->len - 1;

    return BinSearchR_( t, tofind, L, R );

}
