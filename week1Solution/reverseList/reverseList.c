/*
 ============================================================================
 Name        : reverseList.c
 Author      : Peter
 Version     :
 Copyright   : 
 Description : Reverse a linked list.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "reverseList.h"
void reverseList(Node *head) {
	Node *prev = NULL, *next;

	if (head->next == NULL)
		return;

	while (head != NULL) {
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	head = prev;

	return;
}
