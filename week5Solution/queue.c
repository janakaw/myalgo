// queue.c
// a queue of pointers to void

// awirth



#include<stdlib.h>
#include<stdio.h>
#include "queue.h"

#define MAX 1000
#define TRUE (0==0)
#define FALSE (0==1)

// this should probably be done with a struct and a different kind of hiding

static void *Q[MAX];
static int head;
static int tail;
static int full=FALSE;

void
make_empty(void)
{
	head = 0;
	tail = 0;
	full = FALSE;
}

void
inject(void *x)
{
	if(full){
		fprintf(stderr,"Queue is full. Aborting.\n");
		exit(EXIT_FAILURE);
	}
	Q[head] = x;
	head = (head+1) % MAX;
	if(head == tail){
		full=TRUE;
	}
}

void *
eject(void)
{
	void *x;
	x = Q[tail];

	if(head == tail && !full){
		// empty
		fprintf(stderr,"Queue empty. Cannot eject. Aborting.\n");
		exit(EXIT_FAILURE);
	}
	tail = (tail+1) % MAX;
	full = FALSE;

	return x;
}

int
q_size(void)
{
	return ((head + MAX) - tail) % MAX;
}
