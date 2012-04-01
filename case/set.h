#ifndef ih_case_set_h
#define ih_case_set_h

#include "ih/case/list.h"
#include "ih/core/declarations.h"
#include "ih/core/message.h"
#include "ih/core/object.h"

ih_core_bool_t ih_case_set_absorb(ih_case_set_t *set,
    ih_case_set_t *absorb_these);

ih_core_bool_t ih_case_set_absorb_array(ih_case_set_t *set,
    ih_case_array_t *absorb_these);

ih_core_bool_t ih_case_set_absorb_copy(ih_case_set_t *set,
    ih_case_set_t *absorb_these);

ih_core_bool_t ih_case_set_absorb_list_copy(ih_case_set_t *set,
    ih_case_list_t *absorb_these);

ih_core_bool_t ih_case_set_add(ih_case_set_t *set, void *object);

ih_core_bool_t ih_case_set_add_replace(ih_case_set_t *set, void *object);

ih_core_bool_t ih_case_set_add_to_message(ih_case_set_t *set,
    ih_core_message_t *message,
    ih_core_message_add_to_message_f add_to_message);

void ih_case_set_clear(ih_case_set_t *set);

int ih_case_set_compare(void *set_object_a, void *set_object_b);

ih_core_bool_t ih_case_set_contains(ih_case_set_t *superset,
    ih_case_set_t *subset);

void *ih_case_set_copy(void *set_object);

ih_case_set_t *ih_case_set_create(ih_core_iobject_t *iobject);

ih_case_set_t *ih_case_set_create_from_difference(ih_case_set_t *set_a,
    ih_case_set_t *set_b);

ih_case_set_t *ih_case_set_create_from_message
(ih_core_iobject_t *iobject, ih_core_message_t *message,
    ih_core_message_create_from_message_f create_from_message);

ih_case_set_t *ih_case_set_create_from_union(ih_case_set_t *set_a,
    ih_case_set_t *set_b);

void ih_case_set_destroy(void *set_object);

void ih_case_set_dont_destroy_objects(ih_case_set_t *set);

ih_core_bool_t ih_case_set_expunge(ih_case_set_t *set,
    ih_case_set_t *expunge_these);

void *ih_case_set_find(ih_case_set_t *set, void *decoy_object);

void *ih_case_set_find_any(ih_case_set_t *set);

void *ih_case_set_find_copy(ih_case_set_t *set, void *decoy_object);

void *ih_case_set_find_take(ih_case_set_t *set, void *decoy_object);

ih_case_array_t *ih_case_set_get_as_array(ih_case_set_t *set);

ih_case_list_t *ih_case_set_get_as_list(ih_case_set_t *set);

char *ih_case_set_get_as_delimited_string(ih_case_set_t *set,
    ih_core_object_get_as_string_f get_as_string, const char *delimiter);

ih_core_object_compare_f ih_case_set_get_compare_function(ih_case_set_t *set);

ih_core_object_copy_f ih_case_set_get_copy_function(ih_case_set_t *set);

ih_core_object_destroy_f ih_case_set_get_destroy_function(ih_case_set_t *set);

ih_core_iobject_t *ih_case_set_get_iobject(ih_case_set_t *set);

unsigned long ih_case_set_get_size(ih_case_set_t *set);

void ih_case_set_init_iobject(ih_core_iobject_t *iobject);

void *ih_case_set_iterate_next(ih_case_set_t *set);

void ih_case_set_iterate_remove(ih_case_set_t *set);

void ih_case_set_iterate_start(ih_case_set_t *set);

void ih_case_set_lock(ih_case_set_t *set);

ih_core_bool_t ih_case_set_overlaps(ih_case_set_t *set_a,
    ih_case_set_t *set_b);

void ih_case_set_print(ih_case_set_t *set,
    ih_core_object_get_as_string_f get_as_string);

ih_core_bool_t ih_case_set_remove(ih_case_set_t *set, void *object);

void ih_case_set_unlock(ih_case_set_t *set);

#endif
