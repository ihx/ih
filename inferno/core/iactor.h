#ifndef ih_inferno_core_iactor_h
#define ih_inferno_core_iactor_h

#include "ih/core/bitarray.h"

typedef void *(*ih_inferno_core_iactor_create_f)(void *search_system,
    ih_core_bitarray_t *solution);

typedef void *(*ih_inferno_core_iactor_create_random_f)(void *search_system);

typedef ih_core_bitarray_t *(*ih_inferno_core_iactor_get_solution_f)
(void *actor);

struct ih_inferno_core_iactor_t {
  ih_inferno_core_iactor_create_f create;
  ih_inferno_core_iactor_create_random_f create_random;
  ih_core_object_compare_f compare;
  ih_core_object_copy_f copy;
  ih_core_object_destroy_f destroy;
  ih_core_object_get_object_f get_box_cell;
  ih_core_object_set_object_f set_box_cell;
};
typedef struct ih_inferno_core_iactor_t ih_inferno_core_iactor_t;

void ih_inferno_core_iactor_free(ih_inferno_core_iactor_t *iactor);

void ih_inferno_core_iactor_init(ih_inferno_core_iactor_t *iactor,
    ih_inferno_core_iactor_create_f create,
    ih_inferno_core_iactor_create_random_f create_random,
    ih_core_object_compare_f compare, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy,
    ih_core_object_get_object_f get_box_cell,
    ih_core_object_set_object_f set_box_cell);

#endif
