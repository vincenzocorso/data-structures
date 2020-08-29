#include <stdio.h>
#include "queue.h"

int main() {
	queue_ptr queue = queue_create();

	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 10; i++) {
		queue_enqueue(queue, &array[i]);
	}

	printf("nelements: %d\n", queue_get_nelements(queue));

	for(int i = 0; i < 10; i++) {
		printf("dequeue: %d\n", *(int *)queue_dequeue(queue));
	}

	printf("nelements: %d\n", queue_get_nelements(queue));

	printf("is_empty: %d\n", queue_is_empty(queue));

	queue_free(queue);

	return 0;
}