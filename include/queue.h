#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_t *queue_ptr;

/*	Create a new empty queue.
	return: a pointer to the queue.
*/
queue_ptr queue_create();

/*	Check if the queue is empty.
	queue: a pointer to the queue.
	return: 1 if the queue is empty, 0 otherwise.
*/
int queue_is_empty(queue_ptr queue);

/*	Get the number of queue elements.
	queue: a pointer to the queue.
	return: the number of queue elements.
*/
size_t queue_get_nelements(queue_ptr queue);

/*	Push a new element onto the queue.
	queue: a pointer to the queue.
	element_ptr: a pointer to the element to be inserted.
*/
void queue_enqueue(queue_ptr queue, void *element_ptr);

/*	Peek the element on top of the queue.
	queue: a pointer to the queue.
	return: a pointer to the element on top of the queue if it is not empty, NULL otherwise.
*/
void *queue_peek(queue_ptr queue);

/*	Pop the element from the top of the queue.
	queue: a pointer to queue.
	return: a pointer to the element removed from the top if the queue is not empty, NULL otherwise.
*/
void *queue_dequeue(queue_ptr queue);

/*	Free the memory allocated for the queue. The elements are freed.
	queue: a pointer to the queue.
	free_aux: a pointer to a function that frees the memory allocated for an element.
*/
void queue_free_aux(queue_ptr queue, void (*free_aux)(void *element_ptr));

/*	Free the memory allocated for the queue. The elements are not freed.
	queue: a pointer to the queue.
*/
void queue_free(queue_ptr queue);

#endif