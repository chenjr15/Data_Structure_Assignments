#include <stdio.h>
#include "common.h"
#include "Stack.h"
#include "bintree.h"

BinTree* InsertL();
BinTree* InsertElem( BinTree* bt, ElemType* elem_p ) {
    BinTree* bt_head = bt ;
    BinTree* bt_new = CreateBT( elem_p );
    BinTree* bt_parent = NULL;
    while( bt ) {
        bt_parent = bt;
        if( bt_new->data > bt->data ) {
            bt = bt->R;
        } else {
            bt = bt->L;
        }

    }//while( bt )
    if( bt_new->data > bt_parent->data ) {
        bt_parent->R = bt_new;
    } else {
        bt_parent->L =  bt_new;
    }
    return bt_parent;
}

BinTree* BuildBST( ElemType* elemlist, int len ) {
    BinTree* bt_head = CreateBT( elemlist );
    BinTree* bt = bt_head;
    for( int i = 1; i < len; i++ ) {
        InsertElem( bt_head, ++elemlist );
    }//for( int i = 1; i < len; i++ )
    return bt_head;
}//BuildBST()

BinTree* IsBST( BinTree* bt ) {

    if ( !bt ) return INVALID_ARGUMENT;
    LinerStack S;
    LinerStack* pS = &S;
    InitStack( pS );

    while ( !isStackEmpty( pS ) || bt ) {
        /*碰到节点先压栈，然后将指针指向他的左子树，循环直至左子树为空*/
        while ( bt ) {
            PushStack( pS, bt );
            bt = bt->L;
        }
        /*左子树循环完毕，出栈-取出最后压入的节点，然后再使他指向自己的右子树*/
        if ( !isStackEmpty( pS ) ) {
            PopStack( pS, &bt );
            BinTree* badBT = NULL;
            do {
                if( bt->L ) {
                    if( bt->data < bt->L->data ) {
                        badBT = bt;
                        break;
                    }

                } else if ( bt->R ) {
                    if( bt->data > bt->R->data ) {
                        badBT = bt;
                        break;
                    }
                } else if( bt->L && bt->R ) {
                    if( bt->L->data > bt->R->data ) {
                        badBT = bt;
                        break;
                    }
                }
            } while( 0 );
            if( badBT )return badBT;

            bt = bt->R;
        }
    }
    return OK;
}

