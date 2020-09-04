#include <stdlib.h>
#include "dlist.h"

typedef struct dlist_node_t {
	struct dlist_node_t *prev;
	void *element_ptr;
	struct dlist_node_t *next;
} dlist_node_t;

typedef struct dlist_t {
	dlist_node_ptr NIL; // dummy node
} dlist_t;

typedef struct dlist_iter_t {
	dlist_node_ptr next;
	dlist_node_ptr NIL;
	int is_forward;
} dlist_iter_t;

dlist_node_ptr dlist_node_create(void *element_ptr) {
	dlist_node_ptr new_node = malloc(sizeof(dlist_node_t));
	if(new_node != NULL) {
		new_node->element_ptr = element_ptr;
		new_node->prev = new_node->next = NULL;
	}
	return new_node;
}

void *dlist_node_get_element(dlist_node_ptr node) {
	return node->element_ptr;
}

void *dlist_node_free(dlist_node_ptr node) {
	void *element_ptr = node->element_ptr;
	free(node);
	return element_ptr;
}

dlist_ptr dlist_create() {
	dlist_ptr list = malloc(sizeof(dlist_t));
	if(list != NULL) {
		list->NIL = dlist_node_create(NULL);
		list->NIL->prev = list->NIL->next = list->NIL;
	}
	return list;
}

dlist_ptr dlist_copy(dlist_ptr list) {
	dlist_ptr result = dlist_create();
	dlist_node_ptr current_ptr = list->NIL->next;
	while(current_ptr != list->NIL) {
		dlist_node_ptr new_node = dlist_node_create(current_ptr->element_ptr);
		dlist_insert_before(result, NULL, new_node);
		current_ptr = current_ptr->next;
	}
	return result;
}

dlist_node_ptr dlist_get_first(dlist_ptr list) {
	return (list->NIL->next == list->NIL) ? NULL : list->NIL->next;
}

dlist_node_ptr dlist_get_last(dlist_ptr list) {
	return (list->NIL->prev == list->NIL) ? NULL : list->NIL->prev;
}

void dlist_insert_before(dlist_ptr list, dlist_node_ptr node, dlist_node_ptr new_node) {
	if(node == NULL)
		node = list->NIL;
	
	new_node->next = node;
	new_node->prev = node->prev;
	node->prev->next = new_node;
	node->prev = new_node;
}

void dlist_insert_after(dlist_ptr list, dlist_node_ptr node, dlist_node_ptr new_node) {
	if(node == NULL)
		node = list->NIL;
	
	new_node->next = node->next;
	new_node->prev = node;
	node->next->prev = new_node;
	node->next = new_node;
}

void *dlist_delete_before(dlist_ptr list, dlist_node_ptr node) {
	dlist_node_ptr extracted_node = dlist_extract_before(list, node);
	void *element_ptr = extracted_node->element_ptr;
	free(extracted_node);
	return element_ptr;
}

void *dlist_delete_after(dlist_ptr list, dlist_node_ptr node) {
	dlist_node_ptr extracted_node = dlist_extract_after(list, node);
	void *element_ptr = extracted_node->element_ptr;
	free(extracted_node);
	return element_ptr;
}

dlist_node_ptr dlist_extract_before(dlist_ptr list, dlist_node_ptr node) {
	if(node == NULL)
		node = list->NIL;
	
	if(node->prev == list->NIL)
		return NULL;
	
	dlist_node_ptr temp = node->prev;
	temp->prev->next = node;
	node->prev = temp->prev;
	return temp;
}

dlist_node_ptr dlist_extract_after(dlist_ptr list, dlist_node_ptr node) {
	if(node == NULL)
		node = list->NIL;

	if(node->next == list->NIL)
		return NULL;

	dlist_node_ptr temp = node->next;
	temp->next->prev = node;
	node->next = temp->next;
	return temp;
}

static dlist_iter_ptr dlist_iter_create(dlist_ptr list, dlist_node_ptr node, int is_forward) {
	dlist_iter_ptr iter = malloc(sizeof(dlist_iter_t));
	if(iter != NULL) {
		iter->is_forward = is_forward;
		iter->NIL = list->NIL;
		if(node == NULL)
			iter->next = (is_forward) ? dlist_get_first(list) : dlist_get_last(list);
		else
			iter->next = node;
	}
	return iter;
}

dlist_iter_ptr dlist_iter_backward(dlist_ptr list, dlist_node_ptr node) {
	return dlist_iter_create(list, node, 0);
}

dlist_iter_ptr dlist_iter_forward(dlist_ptr list, dlist_node_ptr node) {
	return dlist_iter_create(list, node, 1);
}

int dlist_iter_has_next(dlist_iter_ptr iter) {
	return (iter->next != iter->NIL);
}

dlist_node_ptr dlist_iter_next_node(dlist_iter_ptr iter) {
	dlist_node_ptr node = iter->next;
	iter->next = (iter->is_forward) ? node->next : node->prev;
	return node;
}

void *dlist_iter_next_element(dlist_iter_ptr iter) {
	dlist_node_ptr node = dlist_iter_next_node(iter);
	return node->element_ptr;
}

void dlist_iter_free(dlist_iter_ptr iter) {
	free(iter);
}

void dlist_free_aux(dlist_ptr list, void (*free_aux)(void *element_ptr)) {
	dlist_node_ptr previous_ptr = NULL, current_ptr = list->NIL->next;
	while(current_ptr != list->NIL) {
		previous_ptr = current_ptr;
		current_ptr = current_ptr->next;
		(*free_aux)(previous_ptr->element_ptr);
		free(previous_ptr);
	}
	free(list->NIL);
	free(list);
}

void dlist_free(dlist_ptr list) {
	dlist_node_ptr previous_ptr = NULL, current_ptr = list->NIL->next;
	while(current_ptr != list->NIL) {
		previous_ptr = current_ptr;
		current_ptr = current_ptr->next;
		free(previous_ptr);
	}
	free(list->NIL);
	free(list);
}