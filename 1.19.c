#include <stdio.h>
#include <inttypes.h>
#define BUFFER_SIZE 12
#define O_F(x) printf("%d!=%d\n",x,factorial(x))
uint32_t factorial(uint32_t n);
uint32_t* fun(uint32_t n,uint32_t *a, uint32_t arrsize);
int main(){
	uint32_t i=0;
	uint32_t a[BUFFER_SIZE]={0,};
	//five times test
	for(;i<14;i++){
		printf("\n\n n = %d\n",i);
		if (fun(i,a,BUFFER_SIZE))
			for(uint32_t j=0;j<i;j++)
				printf("%d!*2^%d=%d\n",j,j,a[j]);	
	
		else 
			printf("OVERFLOW\n");
	}
	return 0;
}
uint32_t factorial(uint32_t n){
	uint32_t ret=1,i;
	if(n==0)return 1;
	for(i=1;i<=n;i++)
		ret*=i;
	return ret;

}
uint32_t* fun(uint32_t n,uint32_t *arr, uint32_t arrsize){
	uint32_t ret=1;
	unsigned int k =0;
	if(n>arrsize)return NULL;
	if(n==0){
		arr[0]=1;
		return arr;
	}
	for(k=1;k<n;k++){
		arr[k]=factorial(k)<<k;
		if(arr[k]<arr[k-1]) return NULL;
	}
	
	return arr;

}

