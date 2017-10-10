#include <stdio.h>
#include <stdlib.h>
#define MAXARY 50
typedef int ElemType;
typedef struct {
	ElemType elem[MAXARY];
	int len;

} Linear_list;


Linear_list* join(Linear_list* l1,Linear_list* l2,Linear_list* result);

int isinside(int n,Linear_list* l);
int generate(Linear_list* l, int len);
int output(Linear_list* l);
int isrepeat(Linear_list* l, unsigned int i);

int main(){
	Linear_list l1,l2,result;
	generate(&l1,5);
	generate(&l2,5);
	l1.elem[2]=l1.elem[0];
	l1.elem[3]=l1.elem[0];
	l2.elem[2]=l2.elem[1];
	l2.elem[3]=l2.elem[1];
	result.len=0;
	printf("l1:");
	output(&l1);
	printf("l2:");
	output(&l2);
	printf("re:");
	output(&result);
	join(&l1,&l2,&result);
	
	printf("re:");

	output(&result);
	

}



Linear_list* join(Linear_list* l1,Linear_list* l2,Linear_list* result){
	int i,j;
	for(i=0;i<l1->len;i++){
		if((isinside(l1->elem[i],l2)
		|| isrepeat(l1, i))==0){
			result->elem[result->len]=l1->elem[i];
			result->len++;}}
	for(j=0;j<l2->len;j++){
		if(isrepeat(l2,j)==0){
		result->elem[result->len]=l2->elem[j];
		result->len++;}
	}
	return result;
}

int isinside(int n,Linear_list* l){
	int i=0,in=0;
	for(;i<l->len;i++)
	{
		if(l->elem[i]==n){
			in=1;
			break;
		}
		
	}
return in;
}


int generate(Linear_list* l, int len){
	int i=0;
	l->len=len;
	for(;i<len;i++){
		l->elem[i]=rand()%20;
	}
	return 0;
}

int output(Linear_list* l){
	int i=0;
	for(;i<l->len;i++)
		printf("%d ",l->elem[i]);
	printf(";\n");
	return 0;
}

int isrepeat(Linear_list* l, unsigned int i){
	ElemType *p,*edge,x;
	int repeat=0;
	x=l->elem[i];
	p=l->elem+i;
	edge = l->elem+l->len-1;
	while(p<edge){
		if(x==*(++p)){
			repeat=1;
			break;
			}
		}
	return repeat;
}

