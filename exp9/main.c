#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "bintree.h"
#include "BST.h"

int main( int argc, char* argv[] ) {

    /*获取文件名*/
    char  filename[50];
    if ( argc > 1 ) {
        strncpy( filename, argv [ 1], 49 );

    } else {
        printf( "Please input filename\n" );
        scanf( "%49s", &filename );
    }
    int num = 0;
    /*从文件中读取数据用于构建输入元素列表*/
    FILE* f = fopen( filename, "r" );
    fscanf( f, "%d", &num );
    ElemType* elemlist  = malloc( ( num ) * sizeof( ElemType ) );
    for( int i = 0; i < num; i++ ) {
        fscanf( f, "%d", &( elemlist[i] ) );
    }
    fclose( f );
    BinTree* bt = BuildBST( elemlist, num );
    InTraverse( bt );
    putchar( '\n' );
    printf( "该二叉树%s一个二叉排序树\n", IsBST( bt ) == OK ? "是" : "不是" );
    bt->R->data = -1;
    InTraverse( bt );
    putchar( '\n' );
    printf( "该二叉树%s一个二叉排序树\n", IsBST( bt ) == OK ? "是" : "不是" );
    return 0;

}