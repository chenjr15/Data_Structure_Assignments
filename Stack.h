#ifndef __STACK_H__
#define __STACK_H__
#include "linklist.h"
#define STACK_INIT_LEN 20
#undef ElemType
union vars{
		int i;
		float f;
		char op;
	};
typedef struct {
	union vars elem;
	char type;
} ElemTypeStru;
#define ElemType ElemTypeStru
typedef struct {
	ElemType *base;
	ElemType *top;
	unsigned int size;
}LinerStack;

Status InitStack(LinerStack* S);
Status PushStack(LinerStack* S,ElemType data);
Status PopStack(LinerStack* S,ElemType* data);
ElemType GetTop(LinerStack* S);
void ShowStack(LinerStack* S,unsigned int limit);

#endif
