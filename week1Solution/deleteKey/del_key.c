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
#include "del_key.h"
Node* del_key(int key, Node *head) {
  Node *curr, *tmp, *prev;

  curr = head;

  while (curr != NULL) {
    if (curr->val == key) {
      if (curr == head) {
	prev = curr;
        curr = curr->next;
        head = curr;
	free(prev);
        break;
      }

      prev->next = curr->next;
      free(curr);
      break;
    }
    prev = curr;
    curr = curr->next;
  }
	
     
  return head;
}
