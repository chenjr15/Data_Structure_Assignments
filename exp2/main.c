#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#define compare_pri(l, r) (GetPri(l)-GetPri(r))
typedef struct {
    char op;
    char pri;
} PriStu;

PriStu pries[10] = {
        {'(', 2},
        {'*', 4},
        {'/', 4},
        {'+', 3},
        {'-', 3},
//	{')',2},
//	{'#',1},
};

int Parser( char *str_head, ElemType *elem_array);

Status ToNum(char *str, ElemType *elem);

Status do_judge(ElemType e,LinerStack affix,LinerStack optr);

char GetPri(char op);

int main() {
  LinerStack affix, optr;
  char *inputstr;
  ElemType elem_list[MAX_ELEM_SIZE] = { 0, };
  ElemType temp;
  char op = 0;
  char buffer[100] = {0};
  int elem_count = 0;
  inputstr = buffer;
  InitStack(&affix);
  InitStack(&optr);
  scanf("%50s", inputstr);
  elem_count = Parser(inputstr, elem_list);
  for (int i = 0; i < elem_count; i++) {
    switch (elem_list[i].type) {
      case INTEGER_T:
      case FLOAT_T:
        PushStack(&affix, elem_list[i]);
        break;
      default:
        do_judge(elem_list[i],affix,optr);


    }

  }
  //str ends
  while (INFEASIBLE != PopStack(&optr, &temp)) {
    PushStack(&affix, temp);
  }

  ShowStack(&affix, 0);
  getchar();
  return 0;
}//main


char GetPri(char op) {
  PriStu *p;
  char op_t = 0;
  p = pries;
  while (op_t = (*p).op) {
    if (op_t == op)
      return  (*p).pri;
    p++;
  }
  return 0;
}//GetPri

int Parser( char *str_head, ElemType *elem_array) {
//to Parser str into a array of elements which could be float/integer/operator, it depends on the type
  char *s = str_head, *ns;
  char NumStr[20] = {0};
  ElemType *pElem = elem_array;
  ns = NumStr;
  char c;
  while (c = *s++) {
    if ((c <= '9' && c >= '0') || c == '.') {
      *ns++ = c;
    } else if (GetPri(c)) {
      //is operator
      if (ns != NumStr) {
        ToNum(NumStr, pElem++);
        memset(NumStr, 0, 20);
        ns = NumStr;
      }
      pElem->elem.op = c;
      pElem->type = OPERATOR_T;
      pElem++;

    }//if( GetPri(c))
  }//while
  if (ns != NumStr) {
    ToNum(NumStr, pElem++);
    memset(NumStr, 0, 20);
    ns = NumStr;
  }
//pElem alway fast forward one position than first element
  return pElem - elem_array;
}//Parser
Status ToNum(char *str, ElemType *elem) {
  if (str == NULL || elem == NULL)
    return INVALID_ARGUMENT;
  unsigned int i = 0;
  bool flag = 0;
  while (i < 20 && str[i] != 0) {
    if (str[i++] == '.') {
      flag = 1;
      break;
    }
  }
  if (flag) {
    sscanf(str, "%f", &(elem->elem.f));
    elem->type = FLOAT_T;
  } else {
    sscanf(str, "%d", &(elem->elem.i));
    elem->type = INTEGER_T;
  }

  return OK;

}//ToNum
Status do_judge(ElemType e,LinerStack affix,LinerStack optr) {
  ElemType current={0};
  ElemType top={0};
  switch(e.elem.op){
    case '(':
      PushStack(&optr,e);
      break;
    case ')':
      while(1){
        PopStack(&optr,&current);
        if(current.elem.op == '(') break;
        else PushStack(&affix,current);
      }
      break;
    default:
      if(optr.size>0)
        top = GetTop(&optr);
      else
        top.elem.op = 0;
      if(compare_pri(top.elem.op,e.elem.op)>0){
        //栈内操作符优先级较高,push
        PushStack(&optr,e);
      }
      else{
        //栈内操作符优先级较低或相等
        while(1){
          if(optr.size!=0){
            PopStack(&optr,&top) ;
            PushStack(&affix,top);

          }else top.elem.op=0;
          if(compare_pri(top.elem.op,e.elem.op)<=0){
            PushStack(&optr,e);
            break;
          }
        }//while

      }//else,pri is lower
  }//switch

  return  0;
}


