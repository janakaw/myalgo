// bst.c
// done in workshop 7
// awirth: scaffolding
// apr 11

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "smalloc.h"
#include "record.h"
#include "data.h"

#define MAX 1000

typedef struct l{
	record r;
	struct l *left;
	struct l *right;
} bst;

bool
internal_find(bst **parent, bst **current, bool *left, int key);

void *
make_empty(void)
{
	bst *dummy;
	dummy = (bst *) smalloc(sizeof(bst));
	
	// fill in
}


bool
insert(void *ds,record r)
{
	// fill in so returns FALSE if key already present,
	// and TRUE if key is new
}

bool
internal_find(bst **parent, bst **current, bool *left, int key)
{
	// takes pointers to pointers... so can return multiple things
	// returns TRUE if finds node with key, FALSE otherwise
}

record *
find(void *ds, int key)
{
	// uses internal_find to return either pointer to record, or NULL
}


bool
destroy(void *ds, int key)
{
	// don't do this unless you have finished everything else
	return FALSE;
}

