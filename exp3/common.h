#ifndef __COMMON_H__
#define __COMMON_H__ 


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE_S -1
#define OVERFLOW_S -2
#define INVALID_ARGUMENT -3
#define STACK_INIT_LEN 20

typedef int  Status;

typedef char bool;

typedef char ElemType;
typedef struct bintree {
  ElemType data;
  struct bintree * L;
  struct bintree * R;
} BinTree;
typedef BinTree*  SElemType;


typedef struct {
  SElemType base[STACK_INIT_LEN];
  unsigned int size;
}LinerStack;




#endif // !__COMMON_H__


