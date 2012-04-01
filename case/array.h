#ifndef ih_case_array_h
#define ih_case_array_h

#include "ih/case/declarations.h"
#include "ih/core/bool.h"
#include "ih/core/message.h"
#include "ih/core/object.h"

void ih_case_array_add(ih_case_array_t *array, unsigned long index,
    void *object);

ih_core_bool_t ih_case_array_add_to_message(ih_case_array_t *array,
    ih_core_message_t *message,
    ih_core_message_add_to_message_f add_to_message);

void ih_case_array_clear(ih_case_array_t *array);

int ih_case_array_compare(void *array_object_a, void *array_object_b);

void *ih_case_array_copy(void *array_object);

unsigned long ih_case_array_count_non_null_objects(ih_case_array_t *array);

ih_case_array_t *ih_case_array_create(unsigned long initial_size,
    ih_core_object_compare_f compare, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy);

ih_case_array_t *ih_case_array_create_from_message
(ih_core_object_compare_f compare_object, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, ih_core_message_t *message,
    ih_core_message_create_from_message_f create_from_message);

ih_case_array_t *ih_case_array_create_strings_from_string
(char *string, char *separators);

void ih_case_array_destroy(void *array_object);

void ih_case_array_expunge_set(ih_case_array_t *array,
    ih_case_set_t *expunge_these);

void ih_case_array_expunge_set_inverse(ih_case_array_t *array,
    ih_case_set_t *expunge_all_but_these);

void *ih_case_array_find(ih_case_array_t *array, unsigned long index);

void *ih_case_array_find_random(ih_case_array_t *array);

void *ih_case_array_find_first(ih_case_array_t *array);

void *ih_case_array_find_last(ih_case_array_t *array);

void **ih_case_array_get_array(ih_case_array_t *array);

char *ih_case_array_get_as_delimited_string(ih_case_array_t *array,
    ih_core_object_get_as_string_f get_as_string, char *delimiter);

ih_core_object_compare_f ih_case_array_get_compare(ih_case_array_t *array);

ih_core_object_copy_f ih_case_array_get_copy(ih_case_array_t *array);

ih_core_object_destroy_f ih_case_array_get_destroy(ih_case_array_t *array);

unsigned long ih_case_array_get_size(ih_case_array_t *array);

void *ih_case_array_iterate_next(ih_case_array_t *array);

void ih_case_array_iterate_remove(ih_case_array_t *array);

void ih_case_array_iterate_start(ih_case_array_t *array);

void ih_case_array_print(ih_case_array_t *array);

void ih_case_array_remove(ih_case_array_t *array, unsigned long index);

void ih_case_array_replace(ih_case_array_t *array, unsigned long index,
    void *object);

void ih_case_array_replace_random(ih_case_array_t *array, void *object);

ih_core_bool_t ih_case_array_resize(ih_case_array_t *array,
    unsigned long new_size);

void ih_case_array_sort(ih_case_array_t *array);

#endif
