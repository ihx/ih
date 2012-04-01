#include "ih/case/array.h"
#include "ih/core/bitarray.h"
#include "ih/core/tools.h"
#include "ih/math/combination.h"

struct ih_math_combination_t {
  ih_case_set_t *elements_set;
  ih_case_array_t *elements;
  unsigned long element_count;
  ih_core_bitarray_t *flags;

  ih_core_bool_t iterate_first;

  ih_core_iobject_t *set_iobject;
};

static ih_case_set_t *create_set_based_on_flags
(ih_math_combination_t *combination);

ih_case_set_t *create_set_based_on_flags(ih_math_combination_t *combination)
{
  assert(combination);
  ih_case_set_t *set;
  unsigned long each_element;
  void *object;
  void *object_copy;

  set = ih_case_set_create(combination->set_iobject);
  if (set) {
    for (each_element = 0; each_element < combination->element_count;
         each_element++) {
      if (1 == ih_core_bitarray_get_bit(combination->flags, each_element)) {
        object = ih_case_array_find(combination->elements, each_element);
        object_copy = combination->set_iobject->copy(object);
        if (object_copy) {
          if (!ih_case_set_add(set, object_copy)) {
            ih_core_trace("x_case_set_add");
          }
        } else {
          ih_core_trace("combination->copy");
        }
      }
    }
  } else {
    ih_core_trace("x_case_set_create");
  }

  return set;
}

ih_math_combination_t *ih_math_combination_create(ih_case_set_t *set)
{
  assert(set);
  assert(ih_case_set_get_size(set) > 0);
  ih_math_combination_t *combination;
  ih_core_bool_t so_far_so_good;

  combination = malloc(sizeof *combination);
  if (combination) {
    combination->flags = NULL;
    combination->iterate_first = ih_core_bool_false;
    combination->element_count = ih_case_set_get_size(set);
    combination->set_iobject = ih_case_set_get_iobject(set);
    combination->elements_set = ih_case_set_copy(set);
    if (combination->elements_set) {
      so_far_so_good = ih_core_bool_true;
    } else {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("x_case_set_copy");
    }

  } else {
    so_far_so_good = ih_core_bool_false;

    ih_core_trace("malloc");
  }

  if (so_far_so_good) {
    combination->elements = ih_case_set_get_as_array
      (combination->elements_set);
    if (!combination->elements) {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("x_case_array_create_reference_from_set");
    }
  }

  if (so_far_so_good) {
    combination->flags = ih_core_bitarray_create
      (combination->element_count);
    if (!combination->flags) {
      so_far_so_good = ih_core_bool_false;
    }
  }

  if (!so_far_so_good && combination) {
    if (combination->elements_set) {
      ih_case_set_destroy(combination->elements_set);
    }
    if (combination->elements) {
      ih_case_array_destroy(combination->elements);
    }
    if (combination->flags) {
      ih_core_bitarray_destroy(combination->flags);
    }
  }

  return combination;
}

void ih_math_combination_destroy(ih_math_combination_t *combination)
{
  assert(combination);

  ih_case_set_destroy(combination->elements_set);
  ih_case_array_destroy(combination->elements);
  ih_core_bitarray_destroy(combination->flags);
  free(combination);
}

ih_case_set_t *ih_math_combination_iterate_next
(ih_math_combination_t *combination)
{
  assert(combination);
  ih_case_set_t *set;

  if (combination->iterate_first) {
    set = create_set_based_on_flags(combination);
    if (!set) {
      ih_core_trace("create_set_based_on_flags");
    }
    combination->iterate_first = ih_core_bool_false;
  } else {
    if (ih_core_bitarray_increment(combination->flags)) {
      set = create_set_based_on_flags(combination);
      if (!set) {
        ih_core_trace("create_set_based_on_flags");
      }
    } else {
      set = NULL;
    }
  }

  return set;
}

void ih_math_combination_iterate_start(ih_math_combination_t *combination)
{
  assert(combination);

  ih_core_bitarray_unset_all(combination->flags);
  ih_core_bitarray_set_bit(combination->flags, 0, 1);
  combination->iterate_first = ih_core_bool_true;
}
