/*
 ============================================================================
 Name        : main.c
 Author      : Peter
 Version     :
 Copyright   :
 Description : Creates a linked list from an input file.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "findLen.h"
#include "util.h"

int main(int argc, char **argv) {
	FILE *fp;
	int len, val;
	Node *new_node, *head = NULL, *curr;

	fp = safe_fopen(argv[1], "r");
	while (fscanf(fp, "%d", &val) != EOF) {

		new_node = safe_malloc(sizeof(Node));
		new_node->val = val;
		new_node->next = NULL;

		if (head == NULL) {
			head = new_node;
			curr = head;
		}
		else {
			curr->next = new_node;
			curr = curr->next;
		}
	}

	len = findLen(head);
	printf("Length of the list is %d\n", len);

	return EXIT_SUCCESS;
}

