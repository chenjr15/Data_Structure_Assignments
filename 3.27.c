#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 100

typedef struct{
	long n;
	long m;
} elem; 
typedef struct {
	elem * s;
	unsigned int top;
	
} Stack;

long akm(int m, int n){
	if(m){
		if(n){
			return akm(m-1,akm(m,n-1));
		}
		else{
			return akm(m-1,1);
		}
	}else{
		return n+1;
	}
}

long akm_w(int m,int n){
	int top = 0;
	elem s[STACK_INIT_SIZE];
	memset(s,0,sizeof(elem)*STACK_INIT_SIZE);
	s[top].m = m;
	s[top].n = n;
	
	do{
		while(s[top].m){
			while(s[top].n){
				top++;
				s[top].m=s[top-1].m;
				s[top].n=s[top-1].n-1;
			}//n
			s[top].m--;
			s[top].n = 1;
		}//m
		if(top>0){
			top--;
			s[top].m--;
			s[top].n=s[top+1].n+1;
		}
		
	}while(top != 0 ||s[top].m!=0);//whole
	
	return s[top].n+1;
	
}//akm_w

int main() {
	printf("  递归算法实现：%d\n",akm(2,1));
	printf("非递归算法实现：%d\n",akm_w(2,1));
	getchar();
	return 0;
}
