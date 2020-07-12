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
#include "del_key.h"
#include "util.h"

int main(int argc, char **argv) {
	int val;
	FILE *fp;
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

	printf("Input list\n");
	for (curr = head; curr != NULL; curr = curr->next)
		printf("%d\n", curr->val);

	new_node = del_key(1, head);

	printf("Item removed list\n");
	for (curr = new_node; curr != NULL; curr = curr->next)
			printf("%d\n", curr->val);

	return EXIT_SUCCESS;
}

