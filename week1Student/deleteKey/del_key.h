/*
 * reverseList.h
 *
 *  Created on: 21/07/2011
 *      Author: Peter
 */


typedef struct node Node;
struct node {
   int val;
   Node *next;
};

Node* del_key(int key,Node *head);

