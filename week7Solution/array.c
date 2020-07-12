// array.c

#include <stdlib.h>
#include "smalloc.h"
#include "record.h"
#include "data.h"

#define MAX 1000

typedef struct a{
	record *rs;
	//record rs[MAX];
	int n; // how many items inserted so far
} array;

void *
make_empty(void)
{
	array *A;
	A = (array *) smalloc(sizeof(array));
	A->rs = (record *) smalloc(sizeof(record)*MAX);
	A->n = 0;
	//A->rs = (record *) smalloc(sizeof(*(A->rs))*MAX);
	return A;
}


bool
insert(void *ds,record r)
{
	array *A = (array *) ds;
	if(A->n == MAX){
		// we're full! better do something to warn the user
		//printf("Thai says there's no space!\n");
		return FALSE;
	}
	// put the record into position A->n
	A->rs[A->n] = r; // possibly a problem with the string?
	A->n++;
	return TRUE;
}

record *
find(void *ds, int key)
{
	array *A = (array *) ds;
	record *start = A->rs;
	int i;
	
	for(i=0; i < A->n; i++){
		if(key == start[i].key){
			// set s
			return &start[i];
			// return start+i;
		}
	}
	return NULL;
}


bool
destroy(void *ds, int key)
{
	array *A = (array *) ds;
	record *deathrow;
	
	deathrow = find(ds,key);
	if(deathrow == NULL){
		return FALSE;
	} else {
		*deathrow = A->rs[A->n-1]; //careful
		A->n--;
		return TRUE;
	}
}

