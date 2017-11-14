#include "common.h"
#include "Queue.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

Status InitQueue(queue *D, int len)
{
	if (D == NULL)
		return INVALID_ARGUMENT;
	D->data = malloc(sizeof(SElemType) * len);
	memset(D->data, 0, sizeof(SElemType) * len);
	D->head = 0;
	D->rear = 0;
	D->len = 0;
	return OK;
} //InitQueue

Status EnQueue(queue *D,SElemType *data)
{
	if (D == NULL || data == NULL)
		return INVALID_ARGUMENT;
	if (D->len == QUEUE_LEN)
		return OVERFLOW;
	if (D->len == 0)
		HEAD(D) = *data;
	else
		GET(D, FORWARD(D->head)) = *data;
	(D->len)++;
	return OK;
} //EnQueue

Status DeQueue(queue *D, SElemType *data)
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
} //DeQueue

void OutputQueue(queue *D)
{
	int i;
	for (i = 0; i < QUEUE_LEN; i++)
	{
		printf("%2d ", GET(D, i)->data);
	}
	putchar('\n');
	printf("len:%d", D->len);
	putchar('\n');
} //OutputQueue
Status DestoryQueue(queue *D)
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
} //DestoryQueue