#include <stdio.h> /* For printf */
#include <stdlib.h> /* For malloc */

#include "singly_linked_list.h"

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

void TestListCreate(void);
void TestListInsert(void);
void TestListNext(void);

void TestListTail(void);
void TestListRemove(void);
void TestListSetData(void);
void TestListIsEmpty(void);

void TestListFindData(void);
void TestListForEach();

int AddAll(void *data, void *param);
int IsMatch (const void *data, void *param);

int main ()
{
	
	TestListCreate();
	TestListInsert();
	TestListTail();
	TestListNext();
	TestListRemove();
	TestListSetData();
	TestListIsEmpty();
	TestListFindData();
	TestListForEach();
	
	return 0;
}

void TestListCreate(void)
{
	list_t *my_list = NULL; 
	
	my_list = ListCreate(); /* Creating list and placing dummy node within */
	
	printf("TEST ListCreate\n"); 

	if(0 != ListSize(my_list)) /* using ListSize  */
	{
		printf("%s - failed to allocate memory for list node\n", FAILURE);
	}
	
	else 
	{
		printf("%s - succesfully created list node\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListInsert(void)
{
	int data_1 = 10;
	int data_2 = 20;
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list); 
	
	printf("TEST InsertBefore\n"); 

	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	
	if ( *((int*)ListGetData(iterator)) != data_2 ) 
	{
		printf("%s - failed to insert data\n", FAILURE);
	}
	else
	{
		printf("%s - succesfully inserted data\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListTail(void)
{
	int data_1 = 10;
	int data_2 = 20;
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list); 
	
	printf("TEST ListTail\n"); 
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListTail(my_list);
	
	if ( *((int*)ListGetData(iterator)) != data_2 ) 
	{
		printf("%s - failed to insert data\n", FAILURE);
	}
	else
	{
		printf("%s - succesfully inserted data\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListNext(void)
{
	int data_1 = 10;
	int data_2 = 20;
	float data_3 = 3.14;	
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListInsert(&data_3, iterator);
	
	iterator = ListHead(my_list);
	iterator = ListNext(iterator);

	if ( *((int*)ListGetData(iterator)) != data_2 ) 
	{
		printf("%s failed to iterate node\n", FAILURE);
	}
	else
	{
		printf("%s - succesfully iterated node\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListRemove (void)
{
	
	int data_1 = 10;
	int data_2 = 20;
	float data_3 = 3.14;	
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListInsert(&data_3, iterator);
	
	printf("TEST ListRemove\n"); /* Tests Remove */

	ListRemove(iterator);
	
	if(2 != ListSize(my_list))
	{
		printf("%s - failed to remove data\n", FAILURE);
	}
	else 
	{
		printf("%s - succesfully removed node\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListSetData(void)
{
	int data_1 = 10;
	int data_2 = 20;
	float data_3 = 3.14;	
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListInsert(&data_3, iterator);
	
	printf("TEST ListSetData\n"); /* Tests Remove */
	
	data_3 = 4.20;
	ListSetData(&data_3, iterator);
	
	if ( data_3 != *((float*) ListGetData(iterator)) )
	{
		printf("%s - failed to change value in node\n", FAILURE);
	}
	else
	{
		printf("%s - succesfully changed value node\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}	

void TestListIsEmpty()
{
	int data_1 = 10;
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
		
	printf("TEST ListIsEmpty\n"); 
	if(1 == ListIsEmpty(my_list))
	{
		printf("%s - List is not empty\n", FAILURE);
	}
	else
	{
		printf("%s - List is not empty\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

void TestListFindData()
{
	is_match_function_t is_num_match = IsMatch;
	
	int data_1 = 10;
	int data_2 = 20;
	float data_3 = 3.14;	
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListInsert(&data_3, iterator);
	
	printf("TEST ListFindData\n"); /* Tests Remove */
	
	iterator = ListFindData(ListHead(my_list), ListTail(my_list), is_num_match, &data_3);
	
	if ( data_3 != *((float*) ListGetData(iterator)) )
	{
	 	printf("%s Expected matched data to be: %f \n", FAILURE, data_3);
	}
	else
	{
		printf("%s Found matching data\n", SUCCESS);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

int IsMatch (const void *data, void *criteria)
{
	return (*(double *)data == *(double *)criteria);
}

void TestListForEach()
{
	action_function_t add_all = AddAll;
	
	int data_1 = 10;
	int data_2 = 20;
	float data_3 = 3.14;	
	
	list_t *my_list = NULL; 
	list_iterator_t iterator = NULL;
	
	my_list = ListCreate(); 
	iterator = ListHead(my_list);
	
	iterator = ListInsert(&data_1, iterator);
	iterator = ListInsert(&data_2, iterator);
	iterator = ListInsert(&data_3, iterator);
	
	printf("TEST ListForEach\n"); /* Tests Remove */
	 
	if (!ListForEach(ListHead(my_list),  ListTail(my_list), add_all, &data_1))
	{
		printf("%s For Each succeeded\n", SUCCESS);
	}
	else
	{
	 	printf("%s ForEach failed\n", FAILURE);
	}
	
	ListDestroy(my_list);
	
	printf("\n");
}

int AddAll(void *data, void *param)
{
	*(float *) data += *(float *) param;	
	return 0;
}
