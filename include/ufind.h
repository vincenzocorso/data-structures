#ifndef UFIND
#define UFIND

typedef struct ufind_t *ufind_ptr;
typedef struct ufind_handle_t *ufind_handle_ptr;

/*	Create a empty union-find structure.
	return: a pointer to the union-find.
*/
ufind_ptr ufind_create();

/*	Create a new set in the union-find, containing the given element.
	ufind: a pointer to the union-find.
	element_ptr: a pointer to the element contained in the new set.
	return: a pointer to the element handle in the union-find.
*/
ufind_handle_ptr ufind_makeset(ufind_ptr ufind, void *element_ptr);

/*	Find the representative element of the set that contains the given element.
	ufind: a pointer to the union-find.
	element: a pointer to the element handle in the union-find.
	return: the representative element of the set that contains the given element.
*/
void *ufind_find(ufind_ptr ufind, ufind_handle_ptr element);

/*	Union the two set containing the two given elements.
	ufind: a pointer to the union-find.
	element1: a pointer to an element handle in the union-find.
	element2: a pointer to an element handle in the union-find.
*/
void ufind_union(ufind_ptr ufind, ufind_handle_ptr element1, ufind_handle_ptr element2);

/*	Free the memory allocated for the given union-find structure. The elements are freed.
	ufind: a pointer to the union-find.
	free_aux: a pointer to a function that frees the memory allocated for an element.
*/
void ufind_free_aux(ufind_ptr ufind, void (*free_aux)(void *element_ptr));

/*	Free the memory allocated for the given list. The elements are not freed.
	ufind: a pointer to the union-find.
*/
void ufind_free(ufind_ptr ufind);

#endif