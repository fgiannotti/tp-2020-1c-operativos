#ifndef DELIBIRD_T_LIST_EXTENSION_H
#define DELIBIRD_T_LIST_EXTENSION_H

#include <commons/collections/list.h>

t_list* list_flat(t_list* self);
t_list* list_difference(t_list* self, t_list* other, bool (*comparer) (void*, void*));
t_list* list_swap(t_list* self, int index ,int another_index);
void list_of_lists_destroy_and_destroy_elements(t_list* self,void(*element_destroyer)(void*));
bool list_contains(t_list* self, void* element_to_find, bool (*comparer) (void*, void*));
void list_add_as_set(t_list* self, void* element);
void list_add_as_first(t_list* self, void* element);
void* list_remove_first(t_list* self);
bool is_valid_index(t_list* self, int index);

#endif //DELIBIRD_T_LIST_EXTENSION_H
