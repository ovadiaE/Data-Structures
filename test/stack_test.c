#include <stdio.h> /* For printf */
#include <stdlib.h> /* For Malloc */
#include <stddef.h> /* For size_t */

#include "stack.h"

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int TestStack(void);

int main ()
{
	TestStack();
	
	return 0;
}

int TestStack(void)
{
	stack_t *stack;
	int test1 = 100;
	int test2 = 200;
	int test3 = 300;


	stack = StackCreate(5, 4);
	
	if (NULL == stack)
	{
		printf("%s Stack allocation failed in Test 1\n", FAILURE);
		return -1;
	}
 
	printf("----- TEST PUSH-----\n");
	
	StackPush(stack, &test1);

	if( *( (int*) StackPeek(stack)) != test1 ) /* Use stack peek to test stack pop */
	{
		printf("Test 1 - StackPush: %s - failed to push %d to stack\n", FAILURE, test1 );
	}
	
	StackPush(stack, &test2);
	
	if( *( (int*) StackPeek(stack)) != test2 )
	{
		printf("Test 1 - StackPush: %s - failed to push %d to stack\n", FAILURE, test2 );
	}
	
	else
	{
		printf("%s\n", SUCCESS);
	}
	
	printf("----- TEST POP -----\n");
	
	StackPop(stack);
	
	if( *( (int*) StackPeek(stack)) != test1 ) /* Use stack peek to test stack pop */
	{
		printf("Test 1 - StackPop: %s - failed to pop %d to stack\n", FAILURE, test2 );
	}
	
	else
	{
		printf("%s\n", SUCCESS);
	}
	
	printf("----- TEST SIZE -----\n");
	
	StackPush(stack,&test2);
	StackPush(stack,&test3);
	
	if(3 != StackSize(stack))
	{
		printf("Test 1 - StackSize: %s - EXPECTED size: %d size: %lu \n", FAILURE, 3, StackSize(stack));
	}
	
	else
	{
		printf("%s\n", SUCCESS);
	}
	
	printf("----- TEST ISEMPTY -----\n");
	
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	
	if(1 != StackIsEmpty(stack))
	{
		printf("Test 1 - IsEmpty: %s - EXPECTED result: %d result: %d \n", FAILURE, 1, StackIsEmpty(stack));
	}
	else
	{
		printf("%s\n", SUCCESS);
	}
	
	printf("----- TEST CAPACITY -----\n");
	
	if(5 != StackCapacity(stack))
	{
		printf("Test 1 - StackCapacity: %s - EXPECTED result: %d result: %lu \n", FAILURE, 5, StackCapacity(stack));
	}
	else
	{
		printf("%s\n", SUCCESS);
	}

	return 1;
	
}
