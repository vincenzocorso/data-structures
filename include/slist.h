#ifndef SLIST_H
#define SLIST_H

typedef struct slist_node_t *slist_node_ptr;

/*	Create a new single linked list node.
	element_ptr: a pointer to the element contained in the new node.
	return: a pointer to the new node.
*/
slist_node_ptr slist_node_create(void *element_ptr);

/*	Get the element contained in the given node.
	node: the given node.
	return: the element contained in the given node.
*/
void *slist_node_get_element(slist_node_ptr node);

/*	Free the memory allocated for the given node.
	The element contained in the given node is not freed.
	node: the node to be freed.
	return: a pointer to the element contained in the given node.
*/
void *slist_node_free(slist_node_ptr node);



typedef struct slist_t *slist_ptr;
typedef struct slist_iter_t *slist_iter_ptr;

/*	Create a new empty single linked list.
	return: a pointer to the new list.
*/
slist_ptr slist_create();

/*	Create a shallow copy of the given single linked list.
	list: a pointer to the given list.
	return: a pointer to the copied list.
*/
slist_ptr slist_copy(slist_ptr list);

/*	Get the first list node.
	list: a pointer to the list.
	return: a pointer to the head node or NULL if the list is empty.
*/
slist_node_ptr slist_get_first(slist_ptr list);

/*	Get the last list node.
	list: a pointer to the list.
	return: a pointer to the last node or NULL if the list is empty.
*/
slist_node_ptr slist_get_last(slist_ptr list);

/*	Insert a new node after the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, insert the new node
		  at the beginning of the list.
	new_node: a pointer to the node to be inserted.
*/
void slist_insert_after(slist_ptr list, slist_node_ptr node, slist_node_ptr new_node);

/*	Delete a node after the given node (the node is freed).
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, delete the node
		  at the beginning of the list.
	return: a pointer to the element contained in the node.
*/
void *slist_delete_after(slist_ptr list, slist_node_ptr node);

/*	Extract a node after the given node and return a pointer to it.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, delete the node
		  at the beginning of the list.
	return: a pointer to the node extracted.
*/
slist_node_ptr slist_extract_after(slist_ptr list, slist_node_ptr node);

/*	Create a list iterator that traverses the list forward from the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If NULL the iterator traverse the list from the first node.
	return a pointer to the iterator.
*/
slist_iter_ptr slist_iter_forward(slist_ptr list, slist_node_ptr node);

/*	Check whether the iterator contains elements that have not yet been visited.
	iter: a pointer to the iterator.
	return: 1 if there are elements to visit, 0 otherwise.
*/
int slist_iter_has_next(slist_iter_ptr iter);

/*	Get the next node from the given iterator. The current position increases by one.
	iter: a pointer to the iterator.
	return: a pointer to the node visited.
*/
slist_node_ptr slist_iter_next_node(slist_iter_ptr iter);

/*	Get the next element from the given iterator. The current position increases by one.
	iter: a pointer to the iterator.
	return: a pointer to the element of the node that was visited.
*/
void *slist_iter_next_element(slist_iter_ptr iter);

/*	Free the memory allocated for the given iterator.
	iter: a pointer to the iterator.
*/
void slist_iter_free(slist_iter_ptr iter);

/*	Free the memory allocated for the given list. The elements are freed.
	list: a pointer to the list.
	free_aux: a pointer to a function that frees the memory allocated for an element.
*/
void slist_free_aux(slist_ptr list, void (*free_aux)(void *element_ptr));

/*	Free the memory allocated for the given list. The elements are not freed.
	list: a pointer to the list.
*/
void slist_free(slist_ptr list);

#endif