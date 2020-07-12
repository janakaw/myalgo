// linked.c
// done in class

#include <stdlib.h>
#include "smalloc.h"
#include "record.h"
#include "data.h"

#define MAX 1000

typedef struct l{
	record r;
	struct l *next;
} list;

list *
internal_find(list *dummy,int key);

void *
make_empty(void)
{
	list *dummy;
	dummy = (list *) smalloc(sizeof(list));
	dummy->next = NULL;
	
	return dummy;
}


bool
insert(void *ds,record r)
{
	list *dummy = (list *) ds;
	list *new = (list *) smalloc(sizeof(list));
	new->next = dummy->next;
	dummy->next = new;
	new->r = r;
	return TRUE;
}

list *
internal_find(list *dummy,int key)
{
	list *prev;
	for(prev = dummy; prev->next != NULL; prev = prev->next){
		if(prev->next->r.key == key){
			return prev;
		}
	}
	return NULL;
}

record *
find(void *ds, int key)
{
	list *dummy = (list *) ds;
	list *found;
	if((found = internal_find(dummy,key)) == NULL){
		return NULL;
	} else {
		return &found->next->r;
	}
}


bool
destroy(void *ds, int key)
{
	list *dummy = (list *) ds;
	list *drprev;
	
	drprev = internal_find(dummy,key);
	if(drprev == NULL){
		return FALSE;
	} else {
		list *temp;
		temp = drprev->next;
		drprev->next = temp->next;
		free(temp);
		return TRUE;
	}
}

