/*
 * findLen.h
 *
 *  Created on: 21/07/2011
 *      Author: Peter
 */

#ifndef FINDLEN_H_
#define FINDLEN_H_

typedef struct node Node;
struct node {
   int val;
   Node *next;
};

int findLen(Node *head);

#endif /* FINDLEN_H_ */
