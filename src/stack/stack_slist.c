#include <stdlib.h>
#include "slist.h"
#include "stack.h"

typedef struct stack_t {
	slist_ptr list;
	size_t nelements;
} stack_t;

stack_ptr stack_create() {
	stack_ptr stack = malloc(sizeof(stack_t));
	if(stack != NULL) {
		stack->list = slist_create();
		stack->nelements = 0;
	}
	return stack;
}

int stack_is_empty(stack_ptr stack) {
	return (stack->nelements == 0);
}

size_t stack_get_nelements(stack_ptr stack) {
	return stack->nelements;
}

void stack_push(stack_ptr stack, void *element_ptr) {
	slist_node_ptr new_node = slist_node_create(element_ptr);
	slist_insert_after(stack->list, NULL, new_node);
	(stack->nelements)++;
}

void *stack_peek(stack_ptr stack) {
	if(stack->nelements == 0)
		return NULL;
	
	slist_node_ptr top_node = slist_get_first(stack->list);
	return slist_node_get_element(top_node);
}

void *stack_pop(stack_ptr stack) {
	if(stack->nelements == 0)
		return NULL;

	(stack->nelements)--;
	return slist_delete_after(stack->list, NULL);
}

void stack_free_aux(stack_ptr stack, void (*free_aux)(void *element_ptr)) {
	slist_free_aux(stack->list, free_aux);
}

void stack_free(stack_ptr stack) {
	slist_free(stack->list);
	free(stack);
}