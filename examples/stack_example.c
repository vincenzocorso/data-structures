#include <stdio.h>
#include "stack.h"

int main() {
	stack_ptr stack = stack_create();

	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 10; i++) {
		stack_push(stack, &array[i]);
		printf("push: %d\n", *(int *)stack_peek(stack));
	}

	printf("nelements: %d\n", stack_get_nelements(stack));

	for(int i = 0; i < 10; i++)
		printf("pop: %d\n", *(int *)stack_pop(stack));
	
	printf("is_empty: %d\n", stack_is_empty(stack));

	stack_free(stack);

	return 0;
}