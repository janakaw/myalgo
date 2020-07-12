/*
 ============================================================================
 Name        : findLen.c
 Author      : Peter
 Version     :
 Copyright   : 
 Description : Find the length of a linked list.
 ============================================================================
 */

#include <stdio.h>
#include "findLen.h"

int findLen(Node *head) {
	int len = 0;
	Node *curr;

	curr = head;

	while (curr != NULL) {
		len++;
		curr = curr->next;
	}

	return len;
}
