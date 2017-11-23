#ifndef __COMMON_H__
#define __COMMON_H__

#define TRUE 1
#define FALSE 0
#define MAX(a,b) ((a)>(b)?(a):(b))
typedef enum STATUS {
  OK,
  ERROR,
  INFEASIBLE,
  OVERFLOW,
  INVALID_ARGUMENT
} Status;

#define STACK_INIT_LEN 20

typedef char bool;

typedef char ElemType;
typedef struct bintree
{
  ElemType data;
  struct bintree *L;
  struct bintree *R;
} BinTree;

typedef struct edge{
  int v1,v2;
}Edge;

typedef void*  SElemType;


typedef struct
{
  SElemType base[STACK_INIT_LEN];
  unsigned int size;
} LinerStack;

typedef struct{
	SElemType	*data;
	int head;
	int rear;
	int len;
	
}queue;



#endif // !__COMMON_H__
