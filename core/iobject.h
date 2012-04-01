#ifndef ih_core_iobject_h
#define ih_core_iobject_h

#include "ih/core/object.h"

struct ih_core_iobject_t {
  ih_core_object_compare_f compare;
  ih_core_object_compare_equal_f compare_equal;
  ih_core_object_copy_f copy;
  ih_core_object_destroy_f destroy;
  ih_core_object_get_as_string_f get_as_string;
  ih_core_object_mod_f mod;
};
typedef struct ih_core_iobject_t ih_core_iobject_t;

void ih_core_iobject_init(ih_core_iobject_t *iobject,
    ih_core_object_compare_f compare,
    ih_core_object_compare_equal_f compare_equal,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy,
    ih_core_object_get_as_string_f get_as_string,
    ih_core_object_mod_f mod);

#endif
