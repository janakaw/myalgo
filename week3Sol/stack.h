
// 
// header for stack exercise
//Jul 2011

#define INITIAL_STACK_SIZE 5
#define INPUT_BUFFER_SIZE 100

typedef struct {
        int size;       /* Current size of the items array */

        int top;        /* The element of the array that is the top
                        ** of the stack - you can think of it as the
                        ** next array slot we are going to write into
                        ** when we push a new item onto the stack.
                        */

        int *items;     /* The array of items that is used to represent
                        ** the stack/
                        */
} Stack;

/*
** The four stack operations that need to be implemented:
**
** stack_init() creates a stack of size 'size' and returns
** a pointer to it.
**
** stack_push() pushes 'item' onto the stack pointed to by'stack'.
**
** stack_pop() returns the item that is currently on top of the
** stack and "deletes" it from the stack.
**/
Stack *stack_init(size_t size);
void stack_push(Stack *stack, int item);
int  stack_pop(Stack *stack);
int  stack_is_empty(Stack *stack);

//typedef enum { PUSH, POP, END } StackOp;
//StackOp get_next_operation(FILE *fp, int *number);

//typedef enum { MUL, ADD, NUMB, END} PostOp;
//PostOp get_next_post_operation(FILE *fp, int *number);




