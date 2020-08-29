#ifndef STACK_H
#define STACK_H

typedef struct stack_t *stack_ptr;

/*	Create a new empty stack.
	return: a pointer to the stack.
*/
stack_ptr stack_create();

/*	Check if the stack is empty.
	stack: a pointer to the stack.
	return: 1 if the stack is empty, 0 otherwise.
*/
int stack_is_empty(stack_ptr stack);

/*	Get the number of stack elements.
	stack: a pointer to the stack.
	return: the number of stack elements.
*/
size_t stack_get_nelements(stack_ptr stack);

/*	Push a new element onto the stack.
	stack: a pointer to the stack.
	element_ptr: a pointer to the element to be inserted.
*/
void stack_push(stack_ptr stack, void *element_ptr);

/*	Peek the element on top of the stack.
	stack: a pointer to the stack.
	return: a pointer to the element on top of the stack if it is not empty, NULL otherwise.
*/
void *stack_peek(stack_ptr stack);

/*	Pop the element from the top of the stack.
	stack: a pointer to stack.
	return: a pointer to the element removed from the top if the stack is not empty, NULL otherwise.
*/
void *stack_pop(stack_ptr stack);

/*	Free the memory allocated for the stack. The elements are freed.
	stack: a pointer to the stack.
	free_aux: a pointer to a function that frees the memory allocated for an element.
*/
void stack_free_aux(stack_ptr stack, void (*free_aux)(void *element_ptr));

/*	Free the memory allocated for the stack. The elements are not freed.
	stack: a pointer to the stack.
*/
void stack_free(stack_ptr stack);

#endif