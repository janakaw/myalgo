// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface for postfix evaluation
// Udaya Jul 2011 

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef enum { MUL, ADD, NUMB, END} PostOp;
PostOp get_next_post_operation(FILE *fp, int *number);

int
main(int argc, char **argv)
{
	PostOp operation = END;
	int number,n1,n2 = 0;
	Stack *stack = NULL;

	stack = stack_init(INITIAL_STACK_SIZE);
	
/**
 	while ((operation = get_next_post_operation(stdin, &number)) != END)
	{
		if (operation == ADD)
		{

	printf(" ADD " );
		}
		else if (operation == MUL)
		{
			
	printf(" MUL " );
		}
		else if ( operation == NUMB) 
		{
//	printf(" I am here %d\n", number );
		}
		else
		{
			fprintf(stderr, "Unexpected operation.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	return 0; 

***/


while ((operation = get_next_post_operation(stdin, &number)) != END)
        {
                if (operation == ADD)
                {
                      n1= stack_pop(stack);
                      n2=stack_pop(stack);
                        stack_push(stack, n1+n2);
                }
                else if (operation == MUL)
                {
                   stack_push(stack,stack_pop(stack) * stack_pop(stack));
                }
                else if ( operation == NUMB)
                {
                    stack_push(stack, number);
    //    printf(" I am here \n" );
                }
                else
                {
                        fprintf(stderr, "Unexpected operation.\n");
                        exit(EXIT_FAILURE);
                }
        }
        printf("%d \n", stack_pop(stack));

        return 0;

}

PostOp
get_next_post_operation(FILE *fp, int *number)
{
	char buffer[INPUT_BUFFER_SIZE];
	
	if (fscanf(fp, "%s", buffer) == 1)
	{
		if (buffer[0] == '*')
		{
			return MUL;
		}
		else if (buffer[0] == '+')
		{
			return ADD;
		}
		else if (sscanf(buffer, "%d", number) == 1)
		{
			return NUMB;
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

