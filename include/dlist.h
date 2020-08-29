#ifndef DLIST_H
#define DLIST_H

typedef struct dlist_node_t *dlist_node_ptr;

/*	Create a new double linked list node.
	element_ptr: a pointer to the element contained in the new node.
	return: a pointer to the new node.
*/
dlist_node_ptr dlist_node_create(void *element_ptr);

/*	Get the element contained in the given node.
	node: the given node.
	return: the element contained in the given node.
*/
void *dlist_node_get_element(dlist_node_ptr node);

/*	Free the memory allocated for the given node.
	The element contained in the given node is not freed.
	node: the node to be freed.
	return: a pointer to the element contained in the given node.
*/
void *dlist_node_free(dlist_node_ptr node);



typedef struct dlist_t *dlist_ptr;
typedef struct dlist_iter_t *dlist_iter_ptr;

/*	Create a new empty double linked list.
	return: a pointer to the new list.
*/
dlist_ptr dlist_create();

/*	Get the first list node.
	list: a pointer to the list.
	return: a pointer to the head node or NULL if the list is empty.
*/
dlist_node_ptr dlist_get_first(dlist_ptr list);

/*	Get the last list node.
	list: a pointer to the list.
	return: a pointer to the last node or NULL if the list is empty.
*/
dlist_node_ptr dlist_get_last(dlist_ptr list);

/*	Insert a new node before the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, insert the new node
		  at the end of the list.
	new_node: a pointer to the node to be inserted.
*/
void dlist_insert_before(dlist_ptr list, dlist_node_ptr node, dlist_node_ptr new_node);

/*	Insert a new node after the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, insert the new node
		  at the beginning of the list.
	new_node: a pointer to the node to be inserted.
*/
void dlist_insert_after(dlist_ptr list, dlist_node_ptr node, dlist_node_ptr new_node);

/*	Delete a node before the given node (the node is freed).
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, delete the node
		  at the end of the list.
	return: a pointer to the element contained in the node.
*/
void *dlist_delete_before(dlist_ptr list, dlist_node_ptr node);

/*	Delete a node after the given node (the node is freed).
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, delete the node
		  at the beginning of the list.
	return: a pointer to the element contained in the node.
*/
void *dlist_delete_after(dlist_ptr list, dlist_node_ptr node);

/*	Extract a node before the given node and return a pointer to it.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, extract the node
		  at the end of the list.
	return: a pointer to the node extracted.
*/
dlist_node_ptr dlist_extract_before(dlist_ptr list, dlist_node_ptr node);

/*	Extract a node after the given node and return a pointer to it.
	list: a pointer to the list.
	node: a pointer to the given node. If it's NULL, extract the node
		  at the beginning of the list.
	return: a pointer to the node extracted.
*/
dlist_node_ptr dlist_extract_after(dlist_ptr list, dlist_node_ptr node);

/*	Create a list iterator that traverses the list backward from the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If NULL the iterator traverse the list from the last node.
	return a pointer to the iterator.
*/
dlist_iter_ptr dlist_iter_backward(dlist_ptr list, dlist_node_ptr node);

/*	Create a list iterator that traverses the list forward from the given node.
	list: a pointer to the list.
	node: a pointer to the given node. If NULL the iterator traverse the list from the first node.
	return a pointer to the iterator.
*/
dlist_iter_ptr dlist_iter_forward(dlist_ptr list, dlist_node_ptr node);

/*	Check whether the iterator contains elements that have not yet been visited.
	iter: a pointer to the iterator.
	return: 1 if there are elements to visit, 0 otherwise.
*/
int dlist_iter_has_next(dlist_iter_ptr iter);

/*	Get the next element from the given iterator.
	iter: a pointer to the iterator.
	return: a pointer to the node visited.
*/
dlist_node_ptr dlist_iter_next(dlist_iter_ptr iter);

/*	Free the memory allocated for the given iterator.
	iter: a pointer to the iterator.
*/
void dlist_iter_free(dlist_iter_ptr iter);

/*	Free the memory allocated for the given list. The elements are freed.
	list: a pointer to the list.
	free_aux: a pointer to a function that frees the memory allocated for an element.
*/
void dlist_free_aux(dlist_ptr list, void (*free_aux)(void *element_ptr));

/*	Free the memory allocated for the given list. The elements are not freed.
	list: a pointer to the list.
*/
void dlist_free(dlist_ptr list);

#endif