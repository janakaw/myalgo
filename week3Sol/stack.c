// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface for Stack 


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *
stack_init(size_t size)
{
	Stack *address;

	/*Allocating the previously declared pointer address of type Stack
	**of size Stack
	*/
	address=(Stack *)malloc(sizeof(Stack));

	/*Also allocating the address for address->items 
	**of size (size)
    */
	address->items=(int *)malloc(size*sizeof(int));

		/*Checking both allocated address*/
		if (address==NULL || address->items==NULL)
		{
		fprintf(stderr, "stack_init() NYI.\n");
		exit(EXIT_FAILURE);
		}

	/*Because it is initialization,hence, there will still be no item
	**i.e. top=0 and the provided size of the array= size
	*/
	address->size=size;
	address->top=0;
	
	/*Return the address*/
	return address;
}

void 
stack_push(Stack *stack, int item)
{

	/*Checking the passed argument or address of stack*/ 	
	if (stack==NULL || stack->items==NULL)
	{
	fprintf(stderr, "stack_push() NYI.\n");
	exit(EXIT_FAILURE);
	}

	/*Checking whether the size of the array from the stack
	**has passed the limit
	*/	
	if ((stack->top)>=stack->size) 
	{
	/*If it has ,then reallocate the array*/
	stack->size=stack->size * 2;  
	stack->items=(int *)realloc(stack->items,(stack->size)*sizeof(int));

		/*Do checking again of the address*/	
		if (stack->items==NULL)
		{
		fprintf(stderr, "stack_push() NYI.\n");
		exit(EXIT_FAILURE);
		}
	}

	/*Inserting the item into the stack and incrementing the top*/
	stack->items[stack->top]=item;
	stack->top++;
}

int
stack_pop(Stack *stack)
{
	/*Do checking of the passed argument or address (of the stack)*/
	if (stack==NULL || stack->items==NULL)
	{
	fprintf(stderr, "stack_pop() NYI.\n");
	exit(EXIT_FAILURE);
	}
	
	/*decrementing the top by 1 after being popped*/
	stack->top--;

	/*Returning the popped item*/
	return (stack->items[stack->top]);
}

int
stack_is_empty(Stack *stack)
{
	/*Check the passed argument or address(of the stack)*/
	if (stack==NULL || stack->items==NULL)
	{
	fprintf(stderr, "stack_is_empty() NYI.\n");
	exit(EXIT_FAILURE);
	}

	if (stack->top==0) {
	/*Return 1 if the stack is empty*/ 
	return 1;
	}
	else
	{
	/*OTHERWISE return 0*/
	return 0;
	}

}
