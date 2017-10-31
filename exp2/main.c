#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Stack.h"

#define compare_pri(l, r) (GetPri(l)-GetPri(r))
#define   GetFloat(e)   (((e).type == FLOAT_T)?((e).elem.f):((e).elem.i))
#define NUM_OF_FUNC 7
#define NUM_OF_OP 6

typedef struct {
    char op;
    char pri;
} PriStu;
typedef struct {
    char * funcname;
    int len;
    char op;
    char pri;
}FuncStu;

PriStu pries[NUM_OF_OP] = {
        {'(', 2},
        {'*', 4},
        {'/', 4},
        {'+', 3},
        {'-', 3},
        {')', 2},
//	{'#',1},
};
FuncStu funcs[NUM_OF_FUNC] = {
  {"exp",3,'e',5},
  {"sqrt",4,'s',5},
  {"log10",5,'l',5},
  {"sin",3,'i',5},
  {"cos",3,'o',5},
  {"ln",2,'n',5},
  {"abs",3,'a',5},
};


int Parser(char *str_head, ElemType *elem_array);

Status ToNum(char *str, ElemType *elem);

Status do_judge(ElemType e, LinerStack *suffix_p, LinerStack *optr_p);

Status Operate(LinerStack *suffix_p, ElemType *ret);
void PrintWelcome();

char GetPri(char op);

int main(){
  //------init-----//
  LinerStack suffix, optr;
  char *inputstr;
  ElemType elem_list[MAX_ELEM_SIZE] = { {.elem.i=0,.type = 0},};
  ElemType temp,result;
  char op = 0;
  char buffer[100] = {0};
  int elem_count = 0;
  inputstr = buffer;
  InitStack(&suffix);
  InitStack(&optr);
  //------------//
  PrintWelcome();
  scanf("%s", inputstr);
  elem_count = Parser(inputstr, elem_list);
  for (int i = 0; i < elem_count; i++) {
    switch (elem_list[i].type) {
      case INTEGER_T:
      case FLOAT_T:
        PushStack(&suffix, elem_list[i]);
        break;
      default:
        do_judge(elem_list[i], &suffix, &optr);
        break;
    }//switch
  }//for
  //str ends
  //pop all
  while (INFEASIBLE_S != PopStack(&optr, &temp)) {
    PushStack(&suffix, temp);
  }
  //ShowStack(&suffix, 0);
  Operate(&suffix,&result);
  printf("%g ",result.elem.f);
  getchar();
  getchar();
  return 0;
}//main


char GetPri(char op) {
  //获取优先级
  PriStu *p;
  FuncStu *q;
  char op_t = 0;
  //遍历双目运算符表
  p = pries;
  while ((p - pries)<NUM_OF_OP) {
	  op_t = (*p).op;
	  if (op_t == op)
		  return (*p).pri;
	  p++;
  }
  //遍历双目运算符表
  q = funcs;
  while ((q - funcs)<NUM_OF_FUNC) {
	op_t = (*q).op;
    if (op_t == op)
      return (*q).pri;
    q++;
  }
  return 0;
}//GetPri

int Parser(char *str_head, ElemType *elem_array) {
//to Parser str into a array of elements which could be float/integer/operator, it depends on the type
  char *s = str_head, *ns;
  char NumStr[20] = {0};
  ElemType *pElem = elem_array;
  ns = NumStr;
  char c;
  while (c = *s) {
    if (isdigit(c) || c == '.') {
      *ns++ = c;
      s++;
    } else{
      //is not a digit
      if (ns != NumStr) {
        ToNum(NumStr, pElem++);
        memset(NumStr, 0, 20);
        ns = NumStr;
      }
      do{
        //is operator
		  bool found_flag = 0;
		  for(int i =0; i<NUM_OF_OP;i++)
			  if (pries[i].op == c) {
				  pElem->elem.op = c;
				  pElem->type = OPERATOR_T;
				  pElem++;
				  found_flag = 1;
          s++;
				  break;
			  }
		  if (found_flag)break;
      for(int i = 0; i<NUM_OF_FUNC;i++)
        if(!strncmp(s,funcs[i].funcname,funcs[i].len)){
          s+=funcs[i].len;
          pElem->elem.op = funcs[i].op;
          pElem->type = OPERATOR_PREFIX_T;
          pElem++;
			    break;
			  }
      }while(0);
    }
	}//while
  if(ns != NumStr) {
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
  char * n=NULL;
  if (flag) {
    //sscanf(str, "%f", &(elem->elem.f));
    
    elem->elem.f=strtof(str,n);
    elem->type = FLOAT_T;
  } else {
    elem->elem.i = strtod(str,n);
    elem->type = INTEGER_T;
  }

  return OK;

}//ToNum
Status do_judge(ElemType e, LinerStack *suffix_p, LinerStack *optr_p) {
  ElemType current = {{.i=0},};
  ElemType top = {{.i=0},};
  switch (e.elem.op) {
    case '(':
      PushStack(optr_p, e);
      break;
    case ')':
      while (1) {
        PopStack(optr_p, &current);
        if (current.elem.op == '(') break;
        else PushStack(suffix_p, current);
      }
      break;
    default:
      //非括号的运算符
      if (optr_p->size > 0)
        top = GetTop(optr_p);
      else
        top.elem.op = 0;
      if (compare_pri(e.elem.op, top.elem.op) > 0) {
        //当前优先级高于栈内操作符优先级,push
        PushStack(optr_p, e);

      } else {
        //栈内操作符优先级较低或相等

        while (1) {
          if (optr_p->size != 0) {
            PopStack(optr_p, &top);
            PushStack(suffix_p, top);

          } else top.elem.op = 0;
          if (compare_pri(top.elem.op, e.elem.op) <= 0) {
            PushStack(optr_p, e);
            break;
          }
        }//while


      }//else,pri is lower
  }//switch

  return 0;
}

Status Operate(LinerStack *suffix_p, ElemType *ret) {
  LinerStack S = {{{.elem.i=0}}};
  ElemType a, b, r;
  for (int i = 0; i < suffix_p->size; i++) {
    switch (suffix_p->base[i].type) {
      case INTEGER_T:
      case FLOAT_T:
        PushStack(&S, suffix_p->base[i]);
        break;
      case OPERATOR_T:
        PopStack(&S, &b);
        PopStack(&S, &a);
        switch (suffix_p->base[i].elem.op) {
          case '+':
            r.elem.f = (GetFloat(a) + GetFloat(b));
            break;
          case '-':
            r.elem.f = (GetFloat(a) - GetFloat(b));
            break;
          case '*':
            r.elem.f = (GetFloat(a) * GetFloat(b));
            break;
          case '/':
            r.elem.f = (GetFloat(a) / GetFloat(b));
            break;
          default :
            r.elem.f = 0;
        }
        r.type=FLOAT_T;
        PushStack(&S, r);
        break;

      case OPERATOR_PREFIX_T:
        PopStack(&S, &a);
        switch (suffix_p->base[i].elem.op)
        {
        case 'e':
          r.elem.f = exp(GetFloat(a));
          break;
        case 's':
          r.elem.f = sqrt(GetFloat(a));
          break;
        case 'l':
          r.elem.f = log10(GetFloat(a));
          break;
        case 'i':
          r.elem.f = sin(GetFloat(a));
          break;
        case 'o':
          r.elem.f = cos(GetFloat(a));
          break;
        case 'n':
          r.elem.f = log(GetFloat(a));
          break;
        case 'a':
          r.elem.f = fabs(GetFloat(a));
          break;
        default:
          r.elem.f = 0;
          break;
        }//switch (suffix_p->base[i].elem.op)
        r.type = FLOAT_T;
        PushStack(&S, r);
        break;

      default:
        break;
    }//switch (suffix_p->base[i].type)

  }//for
  PopStack(&S,ret);
  if(ret->type == INTEGER_T){
    ret->type = FLOAT_T;
    ret->elem.f = ret->elem.i;
  }
}
void PrintWelcome() {
  printf("Supported functions:\n");
  for (int i = 0; i < NUM_OF_FUNC; i++)
    printf("%s ",funcs[i].funcname);
  putchar('\n');
  printf("Please input your experssions here:\n");

}



