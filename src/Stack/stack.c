/************************************
* Developer:  Ovi  		            *
* Description: stack.c              * 
*************************************/ 


#include <stddef.h> /* for size_t */
#include <stdlib.h> /* For Malloc */
#include <string.h> /* For memcpy */
#include <assert.h> /* For assert */

#include "stack.h"

struct stack
{
	size_t capacity;
	size_t element_size;
	size_t size;
	char *buffer;
};


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *s = (stack_t*) malloc( sizeof(stack_t) );

	if(NULL == s)
	{
		return NULL;
	}
	
	s->capacity = capacity;

	s-> element_size = element_size;
	
	s->size = 0;
	
	s->buffer = (char*) malloc( capacity * element_size );
	
	if(NULL == s->buffer)
	{
		free(s);
		return NULL;
	}
		
	return s;

}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack->buffer);
	
	free(stack);
}

void StackPush(stack_t *stack, const void *new_element)
{
	assert(stack);
	assert(new_element);
	
	memcpy(&stack->buffer[stack->size * stack->element_size], new_element, stack->element_size);

	++stack->size;
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	
	return stack->buffer + ((stack->size - 1) * stack->element_size);
}

void StackPop(stack_t *stack)
{
	assert(stack);
	
	stack->size -= 1;
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	
	return stack->size;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return (!stack->size);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	
	return stack->capacity;
}
