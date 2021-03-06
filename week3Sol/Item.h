// COMP20003 Algorithms and Data Structures
// Workshop Stacks and Queues
//Interface forQueue
// Created 29/7/20011 Udaya



typedef struct dnode DNode;

struct dnode {
        int item;

        DNode *prev;
                        /*
                        ** The 'prev' field points to the previous node
                        ** in the list, i.e the one in front of this one
                        ** in the queue.
                        */

        DNode *next;

                        /*
                        ** The 'next' field points to the next node in the
                        ** list, i.e. the one behind this one in the queue.
                        */
};


