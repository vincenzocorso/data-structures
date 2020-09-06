#include <stdlib.h>
#include "slist.h"

typedef struct slist_node_t {
	void *element_ptr;
	struct slist_node_t *next;
} slist_node_t;

typedef struct slist_t {
	slist_node_ptr NIL; // dummy node
	slist_node_ptr last;
} slist_t;

typedef struct slist_iter_t {
	slist_node_ptr next;
	slist_node_ptr NIL;
} slist_iter_t;

slist_node_ptr slist_node_create(void *element_ptr) {
	slist_node_ptr new_node = malloc(sizeof(slist_node_t));
	if(new_node != NULL) {
		new_node->element_ptr = element_ptr;
		new_node->next = NULL;
	}
	return new_node;
}

void *slist_node_get_element(slist_node_ptr node) {
	return node->element_ptr;
}

void *slist_node_free(slist_node_ptr node) {
	void *element_ptr = node->element_ptr;
	free(node);
	return element_ptr;
}

slist_ptr slist_create() {
	slist_ptr list = malloc(sizeof(slist_t));
	if(list != NULL) {
		list->NIL = slist_node_create(NULL);
		list->NIL->next = list->NIL;
		list->last = list->NIL;
	}
	return list;
}

slist_ptr slist_copy(slist_ptr list) {
	slist_ptr result = slist_create();
	slist_node_ptr current_ptr = list->NIL->next;
	slist_node_ptr previous_ptr = NULL;
	while(current_ptr != list->NIL) {
		slist_node_ptr new_node = slist_node_create(current_ptr->element_ptr);
		slist_insert_after(result, previous_ptr, new_node);
		previous_ptr = new_node;
		current_ptr = current_ptr->next;
	}
	return result;
}

slist_node_ptr slist_get_first(slist_ptr list) {
	return (list->NIL->next == list->NIL) ? NULL : list->NIL->next;
}

slist_node_ptr slist_get_last(slist_ptr list) {
	return (list->last == list->NIL) ? NULL : list->last;
}

void slist_insert_after(slist_ptr list, slist_node_ptr node, slist_node_ptr new_node) {
	if(node == NULL)
		node = list->NIL;
	
	new_node->next = node->next;
	node->next = new_node;
	if(node == list->last)
		list->last = new_node;
}

void slist_insert_element_after(slist_ptr list, slist_node_ptr node, void *element_ptr) {
	slist_node_ptr new_node = slist_node_create(element_ptr);
	slist_insert_after(list, node, new_node);
}

void *slist_delete_after(slist_ptr list, slist_node_ptr node) {
	slist_node_ptr extracted_node = slist_extract_after(list, node);
	void *element_ptr = extracted_node->element_ptr;
	free(extracted_node);
	return element_ptr;
}

slist_node_ptr slist_extract_after(slist_ptr list, slist_node_ptr node) {
	if(node == NULL)
		node = list->NIL;

	if(node->next == list->NIL)
		return NULL;

	slist_node_ptr temp = node->next;
	node->next = node->next->next;
	if(temp == list->last)
		list->last = node;
	return temp;
}

slist_iter_ptr slist_iter_forward(slist_ptr list, slist_node_ptr node) {
	slist_iter_ptr iter = malloc(sizeof(slist_iter_t));
	if(iter != NULL) {
		iter->next = (node == NULL) ? list->NIL->next : node;
		iter->NIL = list->NIL;
	}
	return iter;
}

int slist_iter_has_next(slist_iter_ptr iter) {
	return (iter->next != iter->NIL);
}

slist_node_ptr slist_iter_next_node(slist_iter_ptr iter) {
	slist_node_ptr node = iter->next;
	iter->next = node->next;
	return node;
}

void *slist_iter_next_element(slist_iter_ptr iter) {
	slist_node_ptr node = slist_iter_next_node(iter);
	return node->element_ptr;
}

void slist_iter_free(slist_iter_ptr iter) {
	free(iter);
}

void slist_free_aux(slist_ptr list, void (*free_aux)(void *element_ptr)) {
	slist_node_ptr previous_ptr = NULL, current_ptr = list->NIL->next;
	while(current_ptr != list->NIL) {
		previous_ptr = current_ptr;
		current_ptr = current_ptr->next;
		(*free_aux)(previous_ptr->element_ptr);
		free(previous_ptr);
	}
	free(list->NIL);
	free(list);
}

void slist_free(slist_ptr list) {
	slist_node_ptr previous_ptr = NULL, current_ptr = list->NIL->next;
	while(current_ptr != list->NIL) {
		previous_ptr = current_ptr;
		current_ptr = current_ptr->next;
		free(previous_ptr);
	}
	free(list->NIL);
	free(list);
}