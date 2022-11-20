#include <stdio.h> 

#include "queue.h"

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

void TestQueueCreate(void);
void TestQueueEnqueue(void);
void TestQueueDequeue(void);
void TestQueueSize(void);
void TestQueueIsEmpty(void);
void TestQueueAppend(void);

int main ()
{
	TestQueueCreate();
	TestQueueEnqueue();
	TestQueueDequeue();
	TestQueueSize();
	TestQueueIsEmpty();
	TestQueueAppend();
	
	return 0;
}

void TestQueueCreate(void)
{
	queue_t *queue = QueueCreate();
	printf("\n");
	printf("----- Test QueCreate -----\n");
	
	if(NULL == queue)
	{
		printf("%s - Failed to create queue\n", FAILURE);
	}
	else
	{
		printf("%s - Succesfully created queue\n", SUCCESS);
	}
	
	QueueDestroy(queue);
	
	printf("\n");
}

void TestQueueEnqueue(void)
{
	queue_t *queue = QueueCreate();
	
	int data_1 = 10;
	int data_2 = 20;
	
	printf("\n");
	printf("----- Test QueEnqueue -----\n");

	QueueEnqueue(queue, &data_1);
	QueueEnqueue(queue, &data_2);

	if(data_1 != *((int*)QueuePeek(queue)))
	{
		printf("%s - Failed to enqueue. EXPECTED: %d RECIEVED: %d\n", FAILURE, data_2, *((int*)QueuePeek(queue)));
	}
	else
	{
		printf("%s - Succesfully enqueued\n", SUCCESS);
	}
	
	QueueDestroy(queue);
	
	printf("\n");
}

void TestQueueDequeue(void)
{
	queue_t *queue = QueueCreate();
	
	int data_1 = 10;
	int data_2 = 20;
	int data_3 = 20;
	int data_4 = 20;
	
	printf("\n");
	printf("----- Test QueDequeue -----\n");

	QueueEnqueue(queue, &data_1);
	QueueEnqueue(queue, &data_2);
	QueueEnqueue(queue, &data_3);
	QueueEnqueue(queue, &data_4);
	
	QueueDequeue(queue);
	QueueDequeue(queue);

	if(data_2 != *((int*)QueuePeek(queue)))
	{
		printf("%s - Failed to dequeue. EXPECTED: %d RECIEVED: %d\n", FAILURE, data_2, *((int*)QueuePeek(queue)));
	}
	else
	{
		printf("%s - Succesfully dequeued\n", SUCCESS);
	}
	
	QueueDestroy(queue);
	
	printf("\n");
}
void TestQueueSize(void)
{
	queue_t *queue = QueueCreate();
	
	int data_1 = 10;
	int data_2 = 20;
	int data_3 = 20;
	int data_4 = 20;
	
	printf("\n");
	printf("----- Test QueSize -----\n");

	QueueEnqueue(queue, &data_1);
	QueueEnqueue(queue, &data_2);
	QueueEnqueue(queue, &data_3);
	QueueEnqueue(queue, &data_4);
	
	QueueDequeue(queue);
	QueueDequeue(queue);

	if(2 != QueueSize(queue))
	{
		printf("%s - Failed EXPECTED size: %d RECIEVED size: %lu\n", FAILURE, 2, QueueSize(queue));
	}
	else
	{
		printf("%s - valid size \n", SUCCESS);
	}
	
	QueueDestroy(queue);
	
	printf("\n");
}

void TestQueueIsEmpty(void)
{
	queue_t *queue = QueueCreate();
	
	int data_1 = 10;
	int data_2 = 20;
	int data_3 = 20;
	
	printf("\n");
	printf("----- Test QueSize -----\n");

	QueueEnqueue(queue, &data_1);
	QueueEnqueue(queue, &data_2);
	QueueEnqueue(queue, &data_3);
	
	QueueDequeue(queue);
	QueueDequeue(queue);
	QueueDequeue(queue);

	if(1 != QueueIsEmpty(queue))
	{
		printf("%s - Expected size: %d size recieved: %lu \n", FAILURE, 0, QueueSize(queue));
	}
	else
	{
		printf("%s - queue is empty \n", SUCCESS);
	}
	
	QueueDestroy(queue);
	
	printf("\n");
}

void TestQueueAppend(void)
{	
	queue_t *queue_1 = QueueCreate();
	queue_t *queue_2 = QueueCreate();
	size_t i = 0;
	int data_1 = 1;
	int data_2 = 2;
	int data_3 = 3;
	
	int data_4 = 4;
	int data_5 = 5;
	int data_6 = 6;
	
	printf("\n");
	printf("----- Test QueAppend ----- \n");

	QueueEnqueue(queue_1, &data_1);
	QueueEnqueue(queue_1, &data_2);
	QueueEnqueue(queue_1, &data_3);
	
	QueueEnqueue(queue_2, &data_4);
	QueueEnqueue(queue_2, &data_5);
	QueueEnqueue(queue_2, &data_6);
	
	QueueAppend(queue_1, queue_2);
	
	for(i = 0; i < 5; ++i)
	{
		QueueDequeue(queue_1);	
	}
	
	if(data_6 != *((int*)QueuePeek(queue_1))) /* Check if queued items are in proper order */
	{
		printf("%s - Failed to concatinate queues EXPECTED value: %d RECIEVED value: %d\n", FAILURE, data_6, *((int*)QueuePeek(queue_1)));
	}
	else
	{
		printf("%s - queues succesfully concatinated \n", SUCCESS);
	}
	
	QueueDestroy(queue_1);
	QueueDestroy(queue_2);
	
	printf("\n");
}
