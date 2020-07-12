// heap.c
// basics of the priority queue implemented as a binary heap (embedded in
// an array)


// awirth
// sep 09
// 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "smalloc.h"
#include "pq.h"
#include "misc.h"
#include "dump.h"

#define MAX MAXNODES

#define FAIL -1

#define p(x) (((x)-1)/2)
#define l(x) (2*(x) + 1)
#define r(x) (2*(x) + 2)

typedef struct hello{
	int treep[MAX];	// records the priority of the ith item in the tree
	int treek[MAX]; // records the key corresponding to the item in the
			// tree
	int loc[MAX];	// records which item in the tree item key is
	int n;		// how many valid values
} hpq;

void
swap(hpq *a, int x, int y);

// given indexes of two items to swap, swap them
void
swap(hpq *a, int x, int y)
{
	int s;
	// swap priorities and keys
	s = a->treep[x];
	a->treep[x] = a->treep[y];
	a->treep[y] = s;

	s = a->treek[x];
	a->treek[x] = a->treek[y];
	a->treek[y] = s;

	// reset the locations of x and y
	a->loc[a->treek[x]] = x;
	a->loc[a->treek[y]] = y;

}

// Creates an empty priority queue
void *
make_empty_pq()
{
	int k;
	hpq *a;

	a = (hpq *) smalloc(sizeof(hpq));	// allocates the arrays etc

	for(k=0;k<MAX;k++){
		a->loc[k] = FAIL;	// no keys are present in the pq yet
		a->treek[k] = FAIL;	// so initialize to FAIL
	}
	a->n = 0;			// so the count is zero
	return (void *) a;
}

// inserts item i with priority p into the priority queue
int
insert_pq(void *ds, int k, int p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y;

	//fprintf(stderr,"INSERTING k %d p %d\n",k,p);

	// check if too many in pq already
	if(a->n == MAX){
		fprintf(stderr,"Too many items in this PQ already. %dth "
		"insertion MAX %d\n",a->n,MAX);
		return FALSE;
	}

	// check if the supplied index is too large
	if(k > MAX){
		fprintf(stderr, "Index %d is too large: maximum allowed is %d\n",
				k,MAX);
		return FALSE;
		// we *could* exit here
		//exit(EXIT_FAILURE);
	}
	// put item k in the last position with priority p
	a->loc[k] = a->n;
	a->treek[a->n] = k;
	a->treep[a->n] = p;


	// start with the location of the new item and its parent
	// while the parent index is valid...
	for(x = p(a->n), y = a->n; x >= 0;){
		// if the parent priority is greater than the child
		if(a->treep[x] > a->treep[y]){
			swap(a,x,y);
			// update the values of x and y for the next iteration
			// can't be done in the for(;;) statement as there is
			// no guarantee as to the order of update
			y = x;
			x = p(x);
		} else {
			// otherwise... finish up
			break;
		}
	}
	
	a->n++;		// increment the count of the number of items in the pq
	//dump_heap(ds);
	return TRUE;
}

// find_min_pq
// just reports what is at the top

int
find_min_pq(void *ds, int *k, int *p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	if(a->n == 0){
		fprintf(stderr,"priority queue is empty, can't delete min\n");
		return FALSE;
	}

	*k = a->treek[0];
	*p = a->treep[0];
	return TRUE;

}

// deletes the key from the pq that has minimum priority
// since we must return two values (the key and its priority) we
// use pointers
// we return a boolean representing whether the queue was non-empty

int
delete_min_pq(void *ds, int *k, int *p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y,z,m;	// m will refer to smaller child

	// check if the pq is empty
	if(a->n == 0){
		fprintf(stderr,"priority queue is empty, can't delete min\n");
		return FALSE;
	}
	// set the i and p values: easy, from the top of the heap and make
	// sure i's location has been set correctly
	*k = a->treek[0];
	*p = a->treep[0];

	// then put last element of heap into top position and update a->n
	swap(a,0,a->n-1);
	a->loc[*k] = FAIL;
	a->n--;
	
	// start the loop to have item (initially) at position 0 sift
	// down the heap
	x = 0;
	y = l(x);
	z = r(x);
	// the main loop should check that the right child is valid
	while(z < a->n){
		// compare the children
		if(a->treep[y] < a->treep[z]){
			m = y;
		} else {
			m = z;
		}
		// compare priority of smaller child with the item itself
		if(a->treep[m] < a->treep[x]){
			// swap if necessary
			swap(a,x,m);
			x = m;
			y = l(m);
			z = r(m);
		} else {
			// if no more swaps, can just exit function
			//dump_heap(ds);
			return TRUE;
		}
	}
	// otherwise, check whether left child is valid
	if(y < a->n){
		// if so, compare left child with item and swap if necessary etc.
		if(a->treep[y] < a->treep[x]){
			swap(a,x,y);
		}
	}
	//dump_heap(ds);
	return TRUE;
	

}

// this takes an key and priority and updates the priority of the key,
// but only to lower it
// the boolean returned indicates whether the priority was indeed lowered

int
decrease_priority_pq(void *ds, int k, int p)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y;

	//dump_heap(ds);
	// get the location of index i, making sure i is in the pq
	if(a->loc[k] == FAIL){
		fprintf(stderr,"Attempt to decrease priority of key %d, not "
			"previously inserted\n",k);
		return FALSE;
	}
	y = a->loc[k];
	if(p >= a->treep[y]){
		// report that no decrease was done, if there was none
		return FALSE;
	} else {
		// if item i's priority will actually be lower, decrease it
		a->treep[y] = p;
		// then do a loop similar to the insert function
		for(x = p(y); x >= 0;){
			if(a->treep[x] > a->treep[y]){
				swap(a,x,y);

				y = x;
				x = p(x);
			} else {
				break;

			}
		}
		return TRUE;
	}
}

void
dump_heap(void *ds)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int i,k;

	fprintf(stderr,"******************* dumping heap **************\n");
	// print out what is in each position
	for(i=0;i<a->n;i++){
		fprintf(stderr,"Position %4d is key %4d priority %12d\n",
			i, a->treek[i], a->treep[i]);
	}
	// for each key that is in the heap, print out what we know about it
	for(k=0;k<MAX;k++){
		if(a->loc[k] != FAIL){
			fprintf(stderr,"Item %4d is in position %4d, "
				"priority %12d\n", k, a->loc[k],
				a->treep[a->loc[k]]);
		}
	}
	fprintf(stderr,"******************* end dumping heap **********\n");
}

// remove the item with key k
int
delete_pq(void *ds, int k)
{
	hpq *a = (hpq *) ds; // does the casting up front
	int x,y,z,m;	// m will refer to smaller child

	// check if the pq is empty
	if(a->n == 0){
		fprintf(stderr,"priority queue is empty, can't delete\n");
		return FALSE;
	}

	x = a->loc[k];

	// then put last element of heap into this position and update a->n
	swap(a,x,a->n-1);
	a->n--;
	
	// start the loop to have item (initially) at position 0 sift
	// down the heap
	y = l(x);
	z = r(x);
	// the main loop should check that the right child is valid
	while(z < a->n){
		// compare the children
		if(a->treep[y] < a->treep[z]){
			m = y;
		} else {
			m = z;
		}
		// compare priority of smaller child with the item itself
		if(a->treep[m] < a->treep[x]){
			// swap if necessary
			swap(a,m,x);
			x = m;
			y = l(x);
			z = r(x);
		} else {
			// if no more swaps, can just exit function
			return TRUE;
		}
	}
	// otherwise, check whether left child is valid
	if(y < a->n){
		// if so, compare left child with item and swap if necessary etc.
		if(a->treep[y] < a->treep[x]){
			swap(a,x,y);
		}
	}
	return TRUE;

}
