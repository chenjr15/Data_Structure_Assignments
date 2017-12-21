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
    /* 用数组构建二叉排序树 */
    BinTree* bt = BuildBST( elemlist, num );
    /* 进行中序遍历输出结果 */
    InTraverse( bt );
    putchar( '\n' );
    /* 测试是否二叉排序树 */
    printf( "该二叉树%s一个二叉排序树\n", IsBST( bt ) == OK ? "是" : "不是" );
    /* 修改其中一个节点,令其不符合规则 */
    bt->R->data = -1;
    /* 对修改后的树进行中序遍历检验结果 */
    InTraverse( bt );
    putchar( '\n' );
    /* 验证IsBST函数的正确性 */
    printf( "该二叉树%s一个二叉排序树\n", IsBST( bt ) == OK ? "是" : "不是" );
    getchar();
    return 0;

}