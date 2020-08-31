#include <stdlib.h>
#include "slist.h"
#include "ufind.h"

typedef struct ufind_handle_t {
	void *element_ptr;
	struct ufind_handle_t *parent;
	int rank;
} ufind_handle_t;

typedef struct ufind_t {
	slist_ptr nodes;
	size_t nelements;
} ufind_t;

ufind_ptr ufind_create() {
	ufind_ptr ufind = malloc(sizeof(ufind_t));
	if(ufind != NULL) {
		ufind->nodes = slist_create();
		ufind->nelements = 0;
	}
	return ufind;
}

static ufind_handle_ptr ufind_handle_create(void *element_ptr) {
	ufind_handle_ptr ufind_handle = malloc(sizeof(ufind_handle_t));
	if(ufind_handle != NULL) {
		ufind_handle->element_ptr = element_ptr;
		ufind_handle->parent = ufind_handle;
		ufind_handle->rank = 0;
	}
	return ufind_handle;
}

ufind_handle_ptr ufind_makeset(ufind_ptr ufind, void *element_ptr) {
	ufind_handle_ptr ufind_handle = ufind_handle_create(element_ptr);
	if(ufind_handle != NULL) {
		slist_node_ptr node = slist_node_create(ufind_handle);
		slist_insert_after(ufind->nodes, NULL, node);
		(ufind->nelements)++;
	}
	return ufind_handle;
}

// path compression
static ufind_handle_ptr _ufind_find(ufind_ptr ufind, ufind_handle_ptr element) {
	if(element->parent != element)
		element->parent = _ufind_find(ufind, element->parent);
	return element->parent;
}

void *ufind_find(ufind_ptr ufind, ufind_handle_ptr element) {
	ufind_handle_ptr handle = _ufind_find(ufind, element);
	return handle->element_ptr;
}

void ufind_union(ufind_ptr ufind, ufind_handle_ptr element1, ufind_handle_ptr element2) {
	ufind_handle_ptr root1 = _ufind_find(ufind, element1);
	ufind_handle_ptr root2 = _ufind_find(ufind, element2);
	if(root1 != root2) {
		if(root1->rank < root2->rank)
			root1->parent = root2;
		else {
			root2->parent = root1;
			if(root1->rank == root2->rank)
				(root1->rank)++;
		}
	}
}

void ufind_free_aux(ufind_ptr ufind, void (*free_aux)(void *element_ptr)) {
	for(int i = 0; i < ufind->nelements; i++) {
		slist_node_ptr node = slist_extract_after(ufind->nodes, NULL);
		ufind_handle_ptr handle = slist_node_get_element(node);
		(*free_aux)(handle->element_ptr);
		free(handle);
	}
	slist_free(ufind->nodes);
	free(ufind);
}

void ufind_free(ufind_ptr ufind) {
	for(int i = 0; i < ufind->nelements; i++) {
		slist_node_ptr node = slist_extract_after(ufind->nodes, NULL);
		ufind_handle_ptr handle = slist_node_get_element(node);
		free(handle);
	}
	slist_free(ufind->nodes);
	free(ufind);
}