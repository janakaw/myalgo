// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface for Stack 

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


typedef enum { PUSH, POP, END } StackOp;
StackOp get_next_operation_frm_file(FILE *fp, int *number);


int
main(int argc, char **argv)
{
	StackOp operation = END;
	int number = 0;
	Stack *stack = NULL;

	stack = stack_init(INITIAL_STACK_SIZE);
	
	while ((operation = get_next_operation_frm_file(stdin, &number)) != END)
	{
		if (operation == PUSH)
		{
			stack_push(stack, number);
		}
		else if ( operation == POP) 
		{
			if (stack_is_empty(stack))
			{
				printf("POP from empty stack.\n");
			}
			else 
			{
				printf("%d\n", stack_pop(stack));	
			}
		}
		else
		{
			fprintf(stderr, "Unexpected operation.\n");
			exit(EXIT_FAILURE);
		}
	}
		
	return 0;
}

// The file consists of integers followed by operands
StackOp get_next_operation_frm_file(FILE *fp, int *number)
{
	char buffer[INPUT_BUFFER_SIZE];
	
	if (fscanf(fp, "%s", buffer) == 1)
	{
		if (buffer[0] == '*')
		{
			return POP;
		}
		else if (sscanf(buffer, "%d", number) == 1)
		{
			return PUSH;
		}
		else
		{
			fprintf(stderr, "Do not recognize %s\n", buffer);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (feof(fp))
		{
			return END;
		}
		else
		{
		       fprintf(stderr, "IO error.\n");
		       exit(EXIT_FAILURE);
		}
	}
}

