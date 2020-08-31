#ifndef UFIND
#define UFIND

typedef struct ufind_t *ufind_ptr;
typedef struct ufind_handle_t *ufind_handle_ptr;

ufind_ptr ufind_create();
ufind_handle_ptr ufind_makeset(ufind_ptr ufind, void *element_ptr);
void *ufind_find(ufind_ptr ufind, ufind_handle_ptr element);
void ufind_union(ufind_ptr ufind, ufind_handle_ptr element1, ufind_handle_ptr element2);
void ufind_free_aux(ufind_ptr ufind, void (*free_aux)(void *element_ptr));
void ufind_free(ufind_ptr ufind);

#endif