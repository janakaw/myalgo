/*
 * reverseList.h
 *
 *  Created on: 21/07/2011
 *      Author: Peter
 */

#ifndef REVERSELIST_H_
#define REVERSELIST_H_

typedef struct node Node;
struct node {
   int val;
   Node *next;
};

void reverseList(Node *head);

#endif /* REVERSELIST_H_ */
