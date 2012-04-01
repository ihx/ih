#ifndef ih_case_list_h
#define ih_case_list_h

#include "ih/case/declarations.h"
#include "ih/core/iobject.h"
#include "ih/core/message.h"
#include "ih/core/object.h"

#define IH_CASE_LIST_NO_SIZE_LIMIT 0

struct ih_case_list_t;
typedef struct ih_case_list_t ih_case_list_t;

ih_core_bool_t ih_case_list_absorb(ih_case_list_t *list,
    ih_case_list_t *absorb_these);

ih_core_bool_t ih_case_list_add_to_message(ih_case_list_t *list,
    ih_core_message_t *message,
    ih_core_message_add_to_message_f add_to_message);

ih_core_bool_t ih_case_list_add_first(ih_case_list_t *list, void *object);

ih_core_bool_t ih_case_list_add_last(ih_case_list_t *list, void *object);

void ih_case_list_clear(ih_case_list_t *list);

int ih_case_list_compare(void *list_object_a, void *list_object_b);

void *ih_case_list_copy(void *list_object);

ih_case_list_t *ih_case_list_create(ih_core_object_compare_f compare,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy);

ih_case_list_t *ih_case_list_create_from_array_n(ih_case_array_t *array,
    unsigned long max_size);

ih_case_list_t *ih_case_list_create_from_message
(ih_core_object_compare_f compare, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, ih_core_message_t *message,
    ih_core_message_create_from_message_f create_from_message);

ih_case_list_t *ih_case_list_create_strings_from_string(char *string,
    const char *separators);

void ih_case_list_destroy(void *list_object);

void ih_case_list_dont_destroy_objects(ih_case_list_t *list);

void *ih_case_list_find_at(ih_case_list_t *list, unsigned long index);

void *ih_case_list_find_first(ih_case_list_t *list);

void *ih_case_list_find_last(ih_case_list_t *list);

void *ih_case_list_find_random(ih_case_list_t *list);

char *ih_case_list_get_as_delimited_string(ih_case_list_t *list,
    ih_core_object_get_as_string_f get_as_string, const char *delimiter);

char *ih_case_list_get_as_string(void *list_object);

unsigned long ih_case_list_get_size(ih_case_list_t *list);

void ih_case_list_init_iobject(ih_core_iobject_t *iobject);

void *ih_case_list_iterate_next(ih_case_list_t *list);

void ih_case_list_iterate_remove(ih_case_list_t *list);

void ih_case_list_iterate_start(ih_case_list_t *list);

void ih_case_list_lock(ih_case_list_t *list);

void ih_case_list_print(void *list_object);

ih_core_bool_t ih_case_list_remove_first(ih_case_list_t *list);

ih_core_bool_t ih_case_list_remove_last(ih_case_list_t *list);

void ih_case_list_set_size_limit(ih_case_list_t *list,
    unsigned long size_limit);

void ih_case_list_unlock(ih_case_list_t *list);

#endif
