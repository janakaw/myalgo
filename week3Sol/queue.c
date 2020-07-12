// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface forQueue 

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *
queue_init(void)
{
	/*Allocating memory for pointer test of size Queue*/
	Queue *test;
	test=(Queue *) malloc (sizeof (Queue));

		/*Checking whether the address returned by malloc is true 
		** instead of NULL
		*/
		if (test==NULL) {
		fprintf(stderr, "queue_init() NYI.\n");
		exit(EXIT_FAILURE);
		}
	
	/*Note that this is initialization of queue , hence, 
	**it is expected that there will still be no item in the queue
	**This generally means the front and the rear will be NULL
	*/
	test->front=NULL;
	test->rear=NULL;
	
	/*Then return the address of test*/
	return test;
}

void
queue_enqueue(Queue *queue, int item)
{
	/* Declaring a pointer called new of type DNode */
	DNode *new;
	
	/*Allocating address for new of size DNode*/
	new=(DNode *)malloc(sizeof(DNode));

	/*Do a checking that the passed argument queue is an address(Not Null)
	**and
	**also whether the allocated address of new is not NULL
	*/

		if (queue == NULL || new == NULL) 
		{ 
		fprintf(stderr, "queue_enqueue() NYI.\n");
        	exit(EXIT_FAILURE);
		}

	/*Inserting the given item into new*/
	new->item=item;

	/*Check whether the queue is still empty or not*/
	if (queue->front == NULL && queue->rear == NULL) {
		
		/*If it is still empty
		**then, let this new item be the first item of queue
		**hence, front and rear points to this item
		* and their next and prev will point to NULL
		*/

		queue->front = new;
		queue->rear = new;
		new->next=NULL;
		new->prev=NULL;
	}
	else
	{
		/*if it is no longer empty
		**then, let the rear of the queue 
		**points to this new item (also remember the next 
		**must point to Null)
		*/

		new->next=NULL;
		new->prev=queue->rear;
		queue->rear=new;
		new->prev->next=new;
	}
}

int
queue_dequeue(Queue *queue) 
{
	DNode *extract;
	int item;

	/*Do checking of the given address of queue*/
	if (queue == NULL) 
	{
	fprintf(stderr, "queue_dequeue() NYI.\n");
        exit(EXIT_FAILURE);
	}

	/*Let the declared variable called item be
	**the item going to be dequeed
	*/
	item=queue->front->item;

	/*extract will be storing the address of queue->front
	**such that it can be freed later on after dequeing
	*/
	extract=queue->front;

	/*Doing the dequeue*/
	queue->front=queue->front->next;


	if (queue->front == NULL) {
		/*If there is no longer an item after dequeing*/
		queue->rear=NULL;
	}
	else 
	{	
		/*If there are still items after dequeing*/
		queue->front->prev=NULL;
	}
	/*free the dequed*/
	free (extract);
	/*Return the value of dequed item*/
	return item;
}

int
queue_is_empty(Queue *queue)
{
	/*Do checking of the given address of queue*/
	if (queue == NULL) 
	{
	fprintf(stderr, "queue_is_empty() NYI.\n");
        exit(EXIT_FAILURE);
	}
	
	/*Check whether there are items left in the queue*/
	if (queue->front == NULL && queue->rear == NULL) {
		/*If the queue is empty, then return true*/
		return 1;
	}
	else
	{
		/*otherwise return false*/
		return 0;
	}
}

