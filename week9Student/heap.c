// heap.c
// basics of the priority queue implemented as a binary heap (embedded in
// an array)
// awirth
// sep 09

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "smalloc.h"
#include "pq.h"
#include "misc.h"
#include "dump.h"

#define MAX 1000

#define FAIL -1

#define p(x) (((x)-1)/2)
#define l(x) (2*(x) + 1)
#define r(x) (2*(x) + 2)

typedef struct hello{
	int treep[MAX];	// records the priority of the ith item in the tree
	int treek[MAX]; // records the key corresponding to the item item in the
			// tree
	int loc[MAX];	// records which item in the tree item key is
	int n;		// how many valid values
} hpq;

// Creates an empty priority queue
void *
make_empty_pq()
{
	int i;
	hpq *a;

	a = (hpq *) smalloc(sizeof(hpq));	// allocates the arrays etc

		// no keys are present in the pq yet
		// so initialize to FAIL
		// so the count is zero
	return (void *) a;
}

// inserts item i with priority p into the priority queue
void
insert_pq(void *ds, int i, int p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y;
	int s;		// used for swapping

	// check if the supplied index is too large
	// put item i in the last position with priority p


	// start with the location of the new item and its parent
	// while the parent index is valid...
		// if the parent priority is greater than the child

			// swap priorities and keys

			// reset the locations of x and y

			// update the values of x and y for the next iteration
			// can't be done in the for(;;) statement as there is
			// no guarantee as to the order of update

			// otherwise... finish up
	
	// increment the count of the number of items in the pq

	
}

// deletes the key from the pq that has minimum priority
// since we must return two values (the key and its priority) we
// use pointers
// we return a boolean representing whether the queue was non-empty

int
delete_min_pq(void *ds, int *i, int *p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y,z,m;	// m will refer to smaller child
	int s;		// for swapping

	// check if the pq is empty

	// set the i and p values: easy, from the top of the heap and make
	// sure i's location has been set correctly

	// then put last element of heap into top position and update a->n
	
	// start the loop to have item (initially) at position 0 sift
	// down the heap

	// the main loop should check that the right child is valid
		// compare the children

		// compare priority of smaller child with the item itself

			// swap if necessary

			// update locations

			// if no more swaps, can just exit function

	// otherwise, check whether left child is valid
		// if so, compare left child with item and swap if necessary etc.
	

}

// this takes an key and priority and updates the priority of the key,
// but only to lower it
// the boolean returned indicates whether the priority was indeed lowered

int
decrease_priority_pq(void *ds, int i, int p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y;
	int s; // for swapping

	// get the location of index i, making sure i is in the pq

		// report that no decrease was done, if there was none

		// if item i's priority will actually be lower, decrease it
		// then do a loop similar to the insert function
}

void
dump_heap(void *ds)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int i;

	fprintf(stderr,"******************* dumping heap **************\n");
	// print out what is in each position

	// for each key that is in the heap, print out what we know about it

	fprintf(stderr,"******************* end dumping heap **********\n");
}
