#include "common.h"
#include "Queue.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

Status InitDeque(deque *D, int len)
{
	if (D == NULL)
		return INVALID_ARGUMENT;
	D->data = malloc(sizeof(SElemType) * len);
	memset(D->data, 0, sizeof(SElemType) * len);
	D->head = 0;
	D->rear = 0;
	D->len = 0;
} //InitDeque

Status EnDeque(deque *D, const SElemType *data)
{
	if (D == NULL || data == NULL)
		return INVALID_ARGUMENT;
	if (D->len == DEQUE_LEN)
		return OVERFLOW;
	if (D->len == 0)
		HEAD(D) = *data;
	else
		GET(D, FORWARD(D->head)) = *data;
	(D->len)++;
	return OK;
} //EnDeque

Status DeDeque(deque *D, SElemType *data)
{
	if (D == NULL || data == NULL)
		return INVALID_ARGUMENT;
	if (D->len == 0)
		return INFEASIBLE;
	*data = REAR(D);
	// BCAKWARD(D->head);
	FORWARD(D->rear);
	
	(D->len)--;
	if(D->len == 0)
		D->head = D->rear;
	return OK;
} //DeDeque

void OutputDeque(deque *D)
{
	int i;
	for (i = 0; i < DEQUE_LEN; i++)
	{
		printf("%2d ", GET(D, i));
	}
	putchar('\n');
	printf("len:%d", D->len);
	putchar('\n');
} //OutputDeque
Status DestoryDeque(deque *D)
{
	if (D == NULL)
		return INVALID_ARGUMENT;
	if (D->data == NULL)
		return INFEASIBLE;
	free(D->data);
	D->data = NULL;
	D->head = 0;
	D->rear = 0;
	D->len = 0;
	return OK;
} //DestoryDeque