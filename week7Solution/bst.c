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
	dummy->left = NULL;
	dummy->right = NULL;
	dummy->r.key = INT_MIN;
	
	return dummy;
}


bool
insert(void *ds,record r)
{
	bst *p = (bst *) ds;
	bst *c = p->right;
	bst *new = (bst *) smalloc(sizeof(bst));
	bool left=FALSE;

	new->r = r;
	new->left = NULL;
	new->right = NULL;

	if(internal_find(&p,&c,&left,r.key)){
		return FALSE;
		// already present
	} else {
		if(left){
			p->left = new;
		} else {
			p->right = new;
		}
	}
	
	return TRUE;
}

bool
internal_find(bst **parent, bst **current, bool *left, int key)
{
	// initially parent is dummy
	// current dummy right
	// left FALSE
#ifdef DEBUG
fprintf(stderr,"in internal_find:\n");
#endif
	while(*current != NULL){
#ifdef DEBUG
		fprintf(stderr,"*current %p\n",*current);
#endif
		if((*current)->r.key == key){
			return TRUE;
		}
		if((*current)->r.key < key){
			*left = FALSE;
			*parent = *current;
			*current = (*current)->right;
		} else {
			*left = TRUE;
			*parent = *current;
			*current = (*current)->left;
		}
	}
	return FALSE;
}

record *
find(void *ds, int key)
{
	bst *p = (bst *) ds;
	bst *c = p->right;
	bool left = FALSE;

	if(internal_find(&p,&c,&left,key)){
		return &(c->r);
	} else {
		return NULL;
	}
}


bool
destroy(void *ds, int key)
{
	return FALSE;
}

