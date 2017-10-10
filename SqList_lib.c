#include "SqList_lib.h"
#include <stdio.h>


/**
 *  \brief Brief
 *  \author ChenJR
 *  \param [in] l : sqlist to print 
 *  \return status, default OK
 *  
 *  \details Print the list 
 */
Status output(SqList* l){
	int i=0;
	for(;i<l->length;i++)
		printf("%d ",l->elem[i]);
	printf("\n");
	return OK;
}


/**
 *  \brief InitList
 *  \author ChenJR
 *  \param [in] l Parameter_Description
 *  \param [in] len Parameter_Description
 *  \return status
 *  
 *  \details Init the len elems of  List l
 */
Status InitList(SqList *l , unsigned len){
	unsigned int i = 0; 
	if ( !l ) return INVALID_ARGUMENT;
	if(len>MAXSIZE) return INVALID_ARGUMENT;
	while(i<len ){
		l->elem[i]=i;
		i++;
		}
	l->length = len;
	return OK;
	
}
