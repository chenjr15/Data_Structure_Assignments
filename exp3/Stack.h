#ifndef __STACK_H__
#define __STACK_H__
#include "common.h"



#define MAX_ELEM_SIZE 100
#define isStackEmpty(p) (!((p)->size))


Status InitStack(LinerStack* S);
Status PushStack(LinerStack* S, SElemType data);
Status PopStack(LinerStack* S, SElemType* data);
SElemType GetTop(LinerStack* S);
void ShowStack(LinerStack* S,unsigned int limit);

#endif
