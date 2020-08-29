#include <stdlib.h>
#include "slist.h"
#include "queue.h"

typedef struct queue_t {
	slist_ptr list;
	size_t nelements;
} queue_t;

queue_ptr queue_create() {
	queue_ptr queue = malloc(sizeof(queue_t));
	if(queue != NULL) {
		queue->list = slist_create();
		queue->nelements = 0;
	}
	return queue;
}

int queue_is_empty(queue_ptr queue) {
	return (queue->nelements == 0);
}

size_t queue_get_nelements(queue_ptr queue) {
	return queue->nelements;
}

void queue_enqueue(queue_ptr queue, void *element_ptr) {
	slist_node_ptr new_node = slist_node_create(element_ptr);
	slist_node_ptr last_node = slist_get_last(queue->list);
	slist_insert_after(queue->list, last_node, new_node);
	(queue->nelements)++;
}

void *queue_peek(queue_ptr queue) {
	if(queue->nelements == 0)
		return NULL;

	slist_node_ptr first_node = slist_get_first(queue->list);
	return slist_node_get_element(first_node);
}

void *queue_dequeue(queue_ptr queue) {
	if(queue->nelements == 0)
		return NULL;
	
	(queue->nelements)--;
	return slist_delete_after(queue->list, NULL);
}

void queue_free_aux(queue_ptr queue, void (*free_aux)(void *element_ptr)) {
	slist_free_aux(queue->list, free_aux);
}

void queue_free(queue_ptr queue) {
	slist_free(queue->list);
	free(queue);
}