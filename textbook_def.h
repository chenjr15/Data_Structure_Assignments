#ifndef __TEXTBOOK_DEF_H__ 
#define __TEXTBOOK_DEF_H__
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define INVALID_ARGUMENT -3

#define MAXSIZE 50

typedef int  Status ;
typedef int ElemType;
typedef char bool;
typedef struct {
	ElemType elem[MAXSIZE];
	int length;

} SqList;
typedef struct  LNode {
	ElemType data;
	struct  LNode *next;
	
}LNode ,*LinkList;


#endif
