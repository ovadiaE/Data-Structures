/*************************************
* Developer:  Ovi  		             *
* Description: Singly_Linked_List.c  *            
**************************************/

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* For malloc */
#include <assert.h> /* For assert */

#include "singly_linked_list.h"

#define TO_NODE(x) (node_t *)(x)
#define TO_ITER(x) (list_iterator_t)(x)
#define TO_LIST(x) (list_t *)(x)
#define UNUSED(x) (void)(x) 

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next_node;
};

struct list
{
	node_t *head;
	node_t *tail;
};

static list_iterator_t CreateNode(void *data, list_iterator_t next_node);
static node_t *GetLastNode(list_iterator_t position);
static int IsTail(node_t *node);
static int IsDummy(node_t *node);
int ListIsSame(list_iterator_t iter1, list_iterator_t iter2);

static int CountSize(void *data, void *param);

list_t *ListCreate(void)
{
	list_t *list = (list_t *)malloc(sizeof(list_t));

	if (NULL == list)
	{
		return NULL;
	}
	
	list->head = CreateNode(list, NULL);
	
	list->tail = list->head ;

	
	return list;
}

list_iterator_t ListHead(const list_t *list)
{
	assert(list);
	
	return (TO_ITER(list->head));
}

list_iterator_t ListTail(const list_t *list)
{
	assert(list);
	
	return (TO_ITER(list->tail));
}

list_iterator_t ListInsert( void *data, list_iterator_t position)
{	
	node_t *new_node = NULL;
	node_t *current_node = TO_NODE(position);

	assert(data);
	assert(TO_NODE(position));
	
	new_node = CreateNode(TO_NODE(position)->data, TO_NODE(position)->next_node);

	if(NULL == new_node) 
	{
		return TO_ITER(GetLastNode(current_node));
	}
	
	if(IsTail(new_node)) 
	{
		((list_t*) new_node->data)->tail = new_node; 
	}
	
	current_node->next_node = new_node;
	current_node->data = data;
	
	return position;

}

list_iterator_t ListNext(list_iterator_t position)
{
	assert(position);
	
	return TO_ITER(TO_NODE(position)->next_node);
}

void ListDestroy(list_t *list)
{
	node_t *temp = NULL;
	node_t *to_free = NULL;
	
	assert(list);
	
	temp = list->head;
	
	while(ListNext(temp))
	{
		
		to_free = temp;
		temp = ListNext(temp);
		free(to_free);		
	}
	
	free(temp);
	free(list);
}

list_iterator_t ListRemove(list_iterator_t position)
{
	node_t *temp = NULL;
	
	assert(position);
	
	position = TO_NODE(position);
	
	temp = position->next_node;
	position->data = temp->data;
	position->next_node = temp->next_node;
	
	if(!IsDummy(temp)) 
	{
		(*(list_t*)temp->data).tail = position; 
	}
	
	free(temp);
	
	return position;
}

void ListSetData(void *data, list_iterator_t position)
{
	assert(position);
	
	(TO_NODE(position))->data = data;
	
}

void *ListGetData(list_iterator_t position)
{
	assert(TO_NODE(position));
	
	return (TO_NODE(position))->data;
}

size_t ListSize(const list_t *list)
{
	size_t count = 0;
	
	assert(list);
	
	ListForEach(ListHead(list), ListTail(list), CountSize, &count);
	
	return (count);

}

int ListIsEmpty(const list_t *list)
{
	assert(list);
	
	return (ListIsSame(ListHead(list),ListTail(list)));	
}

int ListIsSame(list_iterator_t iter1, list_iterator_t iter2)
{
	return (iter1 == iter2);
}

void ListAppend(list_t *dest, list_t *src)
{
	assert(dest);
	assert(src);
	
	dest->tail->next_node = src->head->next_node;
	dest->tail->data = src->head->data;

	dest->tail = src->tail;
	dest->tail->data = dest;

	src->tail = src->head;
	src->tail->data = src;
	src->head->next_node = NULL;
}

list_iterator_t ListFindData(list_iterator_t from, list_iterator_t to, is_match_function_t function, void *param)
{
	assert(TO_NODE(from));
	assert(TO_NODE(to));
	assert(function);

	while (!ListIsSame(from, to))
	{
		if (function(TO_NODE(from)->data, param))
		{
			return from;
		}
		
		from = TO_NODE(from)->next_node;
	}
	
	return to;
}

int ListForEach(list_iterator_t from, list_iterator_t to, action_function_t function, void *param)
{
	int status = 0;	
	
	node_t *node_from = NULL;
	node_t *node_to = NULL;
	
	assert(function);
	assert(from);
	assert(to);
	
	node_from = TO_NODE(from);
	node_to = TO_NODE(to);
	
	while(!ListIsSame(node_from, node_to))
	{
		status = function(node_from->data, param);
		if(status)
		{
			return status;
		}
		
		node_from = node_from->next_node;
	}
	
	return status;
}

static list_iterator_t CreateNode(void *data, list_iterator_t next_node)
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t*));	
	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next_node = next_node;
	
	return new_node;
}

static node_t *GetLastNode(list_iterator_t position)
{
	
	while(!IsDummy(position))
	{
		position = position->next_node;
	}

	return position;
}

static int IsDummy(node_t *node)
{
	node_t *check = TO_NODE(node);
	return(NULL != check->next_node);

}

static int IsTail(node_t *node)
{
	return (NULL == node->next_node);
}


static int CountSize(void *data, void *param)
{
	(void)data;
	assert(param);

	*(size_t*)param += 1; 
			
	return (0);
}
