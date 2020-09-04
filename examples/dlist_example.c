#include <stdio.h>
#include <time.h>
#include "dlist.h"

void print_list_forward(dlist_ptr list);
void print_list_backward(dlist_ptr list);

int main() {
	dlist_ptr list = dlist_create();

	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 10; i++) {
		dlist_node_ptr new_node = dlist_node_create(&array[i]);
		dlist_insert_after(list, NULL, new_node);
	}

	print_list_forward(list);

	int array2[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	for(int i = 0; i < 10; i++) {
		dlist_node_ptr last = dlist_get_last(list);
		dlist_node_ptr new_node = dlist_node_create(&array2[i]);
		dlist_insert_after(list, last, new_node);
	}

	print_list_forward(list);

	int array3[10] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
	for(int i = 0; i < 10; i++) {
		dlist_node_ptr first = dlist_get_first(list);
		dlist_node_ptr new_node = dlist_node_create(&array3[i]);
		dlist_insert_after(list, first, new_node);
	}

	print_list_forward(list);

	int array4[10] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
	for(int i = 0; i < 10; i++) {
		dlist_node_ptr new_node = dlist_node_create(&array4[i]);
		dlist_insert_before(list, NULL, new_node);
	}

	print_list_forward(list);

	int array5[10] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	for(int i = 0; i < 10; i++) {
		dlist_node_ptr first = dlist_get_first(list);
		dlist_node_ptr new_node = dlist_node_create(&array5[i]);
		dlist_insert_before(list, first, new_node);
	}

	print_list_forward(list);

	for(int i = 0; i < 10; i++)
		dlist_delete_after(list, NULL);
	
	print_list_forward(list);

	for(int i = 0; i < 10; i++) {
		dlist_node_ptr first = dlist_get_first(list);
		dlist_delete_after(list, first);
	}

	print_list_forward(list);

	for(int i = 0; i < 10; i++)
		dlist_delete_before(list, NULL);

	print_list_forward(list);

	for(int i = 0; i < 10; i++) {
		dlist_node_ptr last = dlist_get_last(list);
		dlist_delete_before(list, last);
	}

	print_list_forward(list);
	print_list_backward(list);

	dlist_ptr copy = dlist_copy(list);
	print_list_forward(copy);
	print_list_backward(copy);
	dlist_free(copy);

	dlist_free(list);

	return 0;
}

void print_list_forward(dlist_ptr list) {
	dlist_iter_ptr iter = dlist_iter_forward(list, NULL);
	while(dlist_iter_has_next(iter)) {
		dlist_node_ptr node = dlist_iter_next(iter);
		printf("%d --> ", *(int *)dlist_node_get_element(node));
	}
	printf("NULL\n");
	dlist_iter_free(iter);
}

void print_list_backward(dlist_ptr list) {
	dlist_iter_ptr iter = dlist_iter_backward(list, NULL);
	while(dlist_iter_has_next(iter)) {
		dlist_node_ptr node = dlist_iter_next(iter);
		printf("%d --> ", *(int *)dlist_node_get_element(node));
	}
	printf("NULL\n");
	dlist_iter_free(iter);
}