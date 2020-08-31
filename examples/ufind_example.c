#include <stdio.h>
#include "ufind.h"

void print_set(int *array, ufind_ptr ufind, ufind_handle_ptr *handles, size_t size);

int main() {
	ufind_ptr ufind = ufind_create();

	int array[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	ufind_handle_ptr handles[15];
	for(int i = 0; i < 15; i++)
		handles[i] = ufind_makeset(ufind, &array[i]);

	ufind_union(ufind, handles[0], handles[2]);
	ufind_union(ufind, handles[4], handles[6]);
	ufind_union(ufind, handles[8], handles[9]);

	print_set(array, ufind, handles, 15);
	printf("\n");

	ufind_union(ufind, handles[1], handles[3]);
	ufind_union(ufind, handles[6], handles[9]);

	print_set(array, ufind, handles, 15);
	printf("\n");

	ufind_free(ufind);

	return 0;
}

void print_set(int *array, ufind_ptr ufind, ufind_handle_ptr *handles, size_t size) {
	for(int i = 0; i < size; i++)
		printf("%d --> %d\n", array[i], *(int *)ufind_find(ufind, handles[i]));
}