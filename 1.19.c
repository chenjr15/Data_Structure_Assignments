#include <stdio.h>
#include <inttypes.h>
#define BUFFER_SIZE 12
#define MAXINT sizeof(unsigned int)
#define O_F(x) printf("%d!=%d\n",x,factorial(x))

typedef enum {OK, OVERFLOW, OVERSIZE} Status;

Status fun(uint32_t n,uint32_t *a, uint32_t arrsize);
int main(){
	uint32_t n=0;
	uint32_t a[BUFFER_SIZE]={0,};
	
	for(;n<14;n++){
		printf("\nn = %d\n",n);
		Status sta;
		sta = fun(n,a,BUFFER_SIZE);
		switch(sta){
		case OVERFLOW:
			printf("OVERFLOW\n");
			break;
		case OVERSIZE:
			printf("n(%d) is larger than arrsize(%d)!",n,BUFFER_SIZE);
			break;
		default:
			for(uint32_t j=0;j<n;j++)
				printf("%d!*2^%d=%u\n",j,j,a[j]);
			
			}
	}
	return 0;
}

Status fun(uint32_t n,uint32_t *arr, uint32_t arrsize){
	uint32_t ret=1;
	unsigned int k =0;
	if(n>arrsize)return OVERSIZE;
	if(n==0){
		arr[0]=1;
		return OK;
	}
	for(k=1;k<n;k++){
		arr[k]=(arr[k-1]*k)<<1;
		if(arr[k]<arr[k-1]) return OVERFLOW;
	}
	
	return OK;

}

