// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface forQueue 
// Created 29/7/20011 Udaya

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


#define INPUT_BUFFER_SIZE 100

typedef enum { ENQUEUE, DEQUEUE, END } QueueOp;

QueueOp get_next_operation(FILE *fp, int *number);

int
main(int argc, char **argv)
{
	QueueOp operation = END;
	int number = 0;
	Queue *queue = NULL;

	queue = queue_init();
	
	while ((operation = get_next_operation(stdin, &number)) != END)
	{
		if (operation == ENQUEUE)
		{
			queue_enqueue(queue, number);
		}
		else if ( operation == DEQUEUE) 
		{
			if (queue_is_empty(queue))
			{
				printf("DEQUEUE from empty queue.\n");
			}
			else 
			{
				printf("%d\n", queue_dequeue(queue));	
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

QueueOp
get_next_operation(FILE *fp, int *number)
{
	char buffer[INPUT_BUFFER_SIZE];
	
	if (fscanf(fp, "%s", buffer) == 1)
	{
		if (buffer[0] == '*')
		{
			return DEQUEUE; 
		}
		else if (sscanf(buffer, "%d", number) == 1)
		{
			return ENQUEUE;
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


