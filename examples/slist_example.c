#include <stdio.h>
#include <time.h>
#include "slist.h"

void print_list(slist_ptr list);

int main() {
	slist_ptr list = slist_create();

	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 10; i++) {
		slist_node_ptr new_node = slist_node_create(&array[i]);
		slist_insert_after(list, NULL, new_node);
	}

	print_list(list);

	int array2[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	for(int i = 0; i < 10; i++) {
		slist_node_ptr last = slist_get_last(list);
		slist_node_ptr new_node = slist_node_create(&array2[i]);
		slist_insert_after(list, last, new_node);
	}

	print_list(list);

	int array3[10] = {21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
	for(int i = 0; i < 10; i++) {
		slist_node_ptr first = slist_get_first(list);
		slist_node_ptr new_node = slist_node_create(&array3[i]);
		slist_insert_after(list, first, new_node);
	}

	print_list(list);

	for(int i = 0; i < 10; i++)
		slist_delete_after(list, NULL);
	
	print_list(list);

	for(int i = 0; i < 10; i++) {
		slist_node_ptr first = slist_get_first(list);
		slist_delete_after(list, first);
	}

	print_list(list);

	slist_ptr copy = slist_copy(list);
	print_list(copy);
	slist_free(copy);

	slist_free(list);

	return 0;
}

void print_list(slist_ptr list) {
	slist_iter_ptr iter = slist_iter_forward(list, NULL);
	while(slist_iter_has_next(iter)) {
		slist_node_ptr node = slist_iter_next(iter);
		printf("%d --> ", *(int *)slist_node_get_element(node));
	}
	printf("NULL\n");
	slist_iter_free(iter);
}