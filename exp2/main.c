#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#define copmare_pri(l,r) (GetPri(l)-GetPri(r))
typedef struct {
	char op;
	char pri;
} PriStu;

PriStu pries[10]= {
	{'(',2},
	{'*',4},
	{'/',4},
	{'+',3},
	{'-',3},
//	{')',2},
//	{'#',1},
};
ElemType NextElem(char * str);
ElemType* Parser(char * str,ElemType* elemarray);
char GetPri(char op);

int main() {
	LinerStack affix,optr;
	char *inputstr,*ns;
    ElemType c;
	char op=0;
	char buffer[100]= {0};
	char numstr[20]= {0};
	inputstr = buffer;
	ns = numstr;
	InitStack(&affix);
	InitStack(&optr);
	if(scanf("%50s",inputstr))
		while(c=*inputstr++) {
            if(c == '('){
                //左括号，入操作符栈
                PushStack(&optr,c);
            } else if(c == ')'){
                //右括号，出栈直到左括号
                ShowStack(&optr,0);
                ShowStack(&affix,0);
                while(1){
                    PopStack(&optr, &op);
                    if(op=='(') break;
                    else PushStack(&affix,op);
                }//while

            }else if(GetPri(c)){
                //优先级非零为操作符
                if(copmare_pri(c,GetTop(&optr))>0){
                    //栈内操作符优先级较高,push
                    PushStack(&optr,c);
                }else{
                    //栈内操作符优先级较低或相等
                    while(1){
                        op=GetTop(&optr);
                        if(optr.size!=0&&op!='('){
                            PopStack(&optr,&op) ;
                            PushStack(&affix,op);

                        }else op=0;
                        if(copmare_pri(op,c)<=0){
                            PushStack(&optr,c);
                            break;
                        }
                    }//while
                }
            } else{
				//否则为操作数，入后缀栈
				PushStack(&affix,c);
			}//else
			
		}//while
		//str ends
		while(INFEASIBLE != PopStack(&optr, &op)){
			PushStack(&affix,op);
		}
		
    ShowStack(&affix,0);
    getchar();
	return 0;
}//main

char GetPri(char op) {
	PriStu *p;
	char operator = 0;
	p=pries;
	while(operator = (*p).op) {
		if (operator == op )
			return (*p).pri;
		p++;
	}
	return 0;
}//GetPri

ElemType NextElem(char * str){
    continue;

}//NextElem
ElemType* Parser(char * str,ElemType* elemarray){



}
