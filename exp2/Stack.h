#ifndef __STACK_H__
#define __STACK_H__
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE_S -1
#define OVERFLOW_S -2
#define INVALID_ARGUMENT -3


typedef int  Status ;

typedef char bool;

#define STACK_INIT_LEN 20
#define OPERATOR_T ((char)-1)
#define  OPERATOR_PREFIX_T ((char)-2)
#define INTEGER_T 0
#define FLOAT_T 1
#define MAX_ELEM_SIZE 100

union Vars{
    int i;
    float f;
    char op;
};
typedef struct {
    union Vars elem;
    char type;
} ElemType;

typedef struct {
	ElemType base[STACK_INIT_LEN];
	unsigned int size;
}LinerStack;

Status InitStack(LinerStack* S);
Status PushStack(LinerStack* S,ElemType data);
Status PopStack(LinerStack* S,ElemType* data);
ElemType GetTop(LinerStack* S);
void ShowStack(LinerStack* S,unsigned int limit);

#endif
