// merge.c
// code for mergesort
// awirth
// aug 09
// gocer
// august 2011

#include <stdio.h> // for debugging
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "queue.h"
#include "merge.h"
#include "smalloc.h"

// function prototypes

void
merge(int a[], int m, int b[], int n, int c[]);

void
merge_sort_a(int a[], int n, int c[]);

node *
list_merge(node *a, node *b);

void
merge_sort_l(node *head);

void
merge_sort_array(int a[], int n);

void
merge_sort_list(int a[], int n);
/*******************************/


// merge_sort, array style
// creates the auxilliary array to merge into then calls merge_sort_a

void
merge_sort_array(int a[], int n)
{
	int *c;

	if(n > 1){
		c = smalloc(n * sizeof(int));
		merge_sort_a(a,n,c);
		free(c);
	}
}



// merge (into array):
// given sorted array a of ints of length m and
//       sorted array b of ints of length n
// merge them into array c which we can assume is of length m+n

void
merge(int a[], int m, int b[], int n, int c[])
{
	int i;
	// if array a is empty:
	if (m == 0){
		for(i = 0; i < n; i++){
			c[i] = b[i];
		}
		return;
	}

	// if array b is empty:
	if (n == 0){
		for(i = 0; i < m; i++){
			c[i] = a[i];
		}
		return;
	}

	// otherwise compare the candidates
	if(a[0]<= b[0]){
		c[0] = a[0];
		// and recurse
		merge(a+1,m-1,b,n,c+1);
	} else {
		c[0] = b[0];
		merge(a,m,b+1,n-1,c+1);
	}
}


//merge_sort_a, given array a of length n and auxilliary array c
//use a divide and conquer approach, with the merge function, to
// put a sorted version of a BACK INTO a.

void
merge_sort_a(int a[], int n, int c[])
{
	int i;
	if(n > 1){
		merge_sort_a(a,n/2,c);
		merge_sort_a(a+n/2,n-n/2,c);
		merge(a,n/2,a+n/2,n-n/2,c);
		for(i=0;i<n;i++){
			a[i] = c[i];
		}
	}
}


// merge_sort, linked-list style
// given an array of ints, create a linked list of the same ints
// call merge_sort_l, then put the sorted ints back into the array

void
merge_sort_list(int a[], int n)
{
	int i;
	node *head;
	node *new;
	node *now, *temp;

	head = (node *) smalloc(sizeof(node));
	head->next = NULL;

	for(i=n-1;i>=0;i--){
		new = (node *) smalloc(sizeof(node));
		new-> r = a[i];
		new -> next = head->next;
		head->next = new;
	}
	merge_sort_l(head);

	for(i=0, now = head; i<n ; i++){
		a[i] = now->next->r;
		temp = now;
		now = now->next;
		free(temp);
	}

}

// merge_sort_l:
// given a linked list WITH a dummy head node, use the algorithm at the
// bottom of page 51 of the text, with the function list_merge,
// to effect a sort.

// you will need to refer to the functions in queue.h and queue.c too.

void
merge_sort_l(node *head)
{
	node *now;
	node *single;
	node *a;
	node *b;
	node *c;

	if(head->next == NULL){
		return;
	}

	make_empty();

	// NOTE:
        // one of the steps is:
	// from the linked list pointed to by the dummy head node,
	// produce a bunch of singleton lists without dummy head nodes
	
	for(now = head->next; now != NULL;){
		single = now;
		now = now -> next;
		single->next = NULL;
		inject((void *) single);
		
	}
	
	while(q_size() > 1){
		a = (node *) eject();
		b = (node *) eject();
		c = list_merge(a,b);
		inject((void *) c);
	}

	head->next = (node *) eject();
}



// list_merge:
// given two sorted lists WITHOUT dummy head nodes, merge them, returning
// the consequent list

node *
list_merge(node *a, node *b)
{
	node *rest;

	// if a is empty:
	if(a == NULL){
		return b;
	}
	// if b is empty:
	if(b == NULL){
		return a;
	}

	// otherwise compare the keys in the ints
	if(a->r <= b->r){
		// merge the remainder and attach to the first node
		rest = list_merge(a->next,b);
		a->next = rest;
		return a;
	} else {
		rest = list_merge(a,b->next);
		b->next = rest;
		return b;
	}

}







