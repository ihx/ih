#include "ih/case/array.h"
#include "ih/core/basic/long.h"
#include "ih/case/set.h"

#if defined IH_CASE_SET_IMPL_BINARY_TREE
#include "ih/case/set.impl.binary_tree.c"
#elif defined IH_CASE_SET_IMPL_HASH_TABLE
#include "ih/case/set.imple.hash_table.c"
#elif defined IH_CASE_SET_IMPL_HASHA
#include "ih/case/set.impl.hasha.c"
#elif defined IH_CASE_SET_IMPL_IMPL_MBIN
#include "ih/case/set.impl.mbin.c"
#elif defined IH_CASE_SET_SKIP_IMPL_LIST
#include "ih/case/set.impl.skip_list.c"
#else
#include "ih/case/set.impl.binary_tree.c"
#endif

ih_core_bool_t ih_case_set_absorb(ih_case_set_t *set,
    ih_case_set_t *absorb_these)
{
  assert(set);
  assert(absorb_these);
  void *object;
  ih_core_bool_t success;

  success = ih_core_bool_true;

  ih_case_set_iterate_start(absorb_these);
  while ((object = ih_case_set_iterate_next(absorb_these))) {
    if (!ih_case_set_add(set, object)) {
      success = ih_core_bool_false;
      ih_core_trace("x_case_set_add");
    }
  }

  return success;
}

ih_core_bool_t ih_case_set_absorb_array(ih_case_set_t *set,
    ih_case_array_t *absorb_these)
{
  assert(set);
  assert(absorb_these);
  void *object;
  ih_core_bool_t success;

  success = ih_core_bool_true;

  ih_case_array_iterate_start(absorb_these);
  while ((object = ih_case_array_iterate_next(absorb_these))) {
    if (!ih_case_set_add(set, object)) {
      success = ih_core_bool_false;
      ih_core_trace("x_case_set_add");
    }
  }

  return success;
}

ih_core_bool_t ih_case_set_absorb_copy(ih_case_set_t *set,
    ih_case_set_t *absorb_these)
{
  assert(set);
  assert(absorb_these);
  assert(ih_case_set_get_iobject(set)->destroy);
  void *object;
  void *object_copy;
  ih_core_bool_t success;
  ih_core_iobject_t *iobject = ih_case_set_get_iobject(set);

  success = ih_core_bool_true;

  ih_case_set_iterate_start(absorb_these);
  while ((object = ih_case_set_iterate_next(absorb_these))) {
    object_copy = iobject->copy(object);
    if (object_copy) {
      if (!ih_case_set_add(set, object_copy)) {
        iobject->destroy(object_copy);
      }
    } else {
      success = ih_core_bool_false;
      ih_core_trace("copy");
    }
  }

  return success;
}

ih_core_bool_t ih_case_set_absorb_list_copy(ih_case_set_t *set,
    ih_case_list_t *absorb_these)
{
  assert(set);
  assert(absorb_these);
  assert(ih_case_set_get_iobject(set)->destroy);
  void *object;
  void *object_copy;
  ih_core_bool_t success;
  ih_core_iobject_t *iobject = ih_case_set_get_iobject(set);

  success = ih_core_bool_true;

  ih_case_list_iterate_start(absorb_these);
  while ((object = ih_case_list_iterate_next(absorb_these))) {
    object_copy = iobject->copy(object);
    if (object_copy) {
      if (!ih_case_set_add(set, object_copy)) {
        iobject->destroy(object_copy);
      }
    } else {
      success = ih_core_bool_false;
      ih_core_trace("copy");
    }
  }

  return success;
}

ih_core_bool_t ih_case_set_add_to_message(ih_case_set_t *set,
    ih_core_message_t *message,
    ih_core_message_add_to_message_f add_to_message)
{
  ih_core_bool_t success;
  long set_size;
  void *object;

  set_size = ih_case_set_get_size(set);
  success = ih_core_message_add_long(message, &set_size);
  ih_case_set_iterate_start(set);
  while ((object = ih_case_set_iterate_next(set))) {
    if (!add_to_message(object, message)) {
      success = ih_core_bool_false;
      break;
    }
  }

  return success;
}

void ih_case_set_clear(ih_case_set_t *set)
{
  assert(set);

  ih_case_set_iterate_start(set);
  while (ih_case_set_iterate_next(set)) {
    ih_case_set_iterate_remove(set);
  }
}

int ih_case_set_compare(void *set_object_a,
    void *set_object_b)
{
  assert(set_object_a);
  assert(set_object_b);
  ih_case_set_t *set_a;
  ih_case_set_t *set_b;
  int compare_result;
  void *object_a;
  void *object_b;
  unsigned long size_a;
  unsigned long size_b;
  ih_core_object_compare_f compare;

  set_a = set_object_a;
  set_b = set_object_b;

  size_a = ih_case_set_get_size(set_a);
  size_b = ih_case_set_get_size(set_b);

  compare_result = ih_core_basic_long_compare(&size_a, &size_b);
  if (0 == compare_result) {
    compare = ih_case_set_get_iobject(set_a)->compare;
    ih_case_set_iterate_start(set_a);
    ih_case_set_iterate_start(set_b);
    while ((object_a = ih_case_set_iterate_next(set_a))) {
      object_b = ih_case_set_iterate_next(set_b);
      compare_result = compare(object_a, object_b);
      if (0 != compare_result) {
        break;
      }
    }
  }

  return compare_result;
}

ih_core_bool_t ih_case_set_contains(ih_case_set_t *superset,
    ih_case_set_t *subset)
{
  assert(superset);
  assert(subset);
  ih_core_bool_t contains_it;
  void *object;

  contains_it = ih_core_bool_true;

  ih_case_set_iterate_start(subset);
  while ((object = ih_case_set_iterate_next(subset))) {
    if (!ih_case_set_find(superset, object)) {
      contains_it = ih_core_bool_false;
      break;
    }
  }

  return contains_it;
}

void *ih_case_set_copy(void *set_object)
{
  assert(set_object);
  ih_case_set_t *set = set_object;
  ih_case_set_t *copy;
  void *original_object;
  void *copied_object;
  ih_core_iobject_t *iobject = ih_case_set_get_iobject(set);

  copy = ih_case_set_create(iobject);
  if (copy) {
    ih_case_set_iterate_start(set);
    while ((original_object = ih_case_set_iterate_next(set))) {
      copied_object = iobject->copy(original_object);
      if (copied_object) {
        if (!ih_case_set_add(copy, copied_object)) {
          ih_core_trace("x_case_set_add");
          iobject->destroy(copied_object);
          ih_case_set_destroy(copy);
          copy = NULL;
          break;
        }
      } else {
        ih_core_trace("copy");
        ih_case_set_destroy(copy);
        copy = NULL;
        break;
      }
    }
  } else {
    ih_core_trace("x_case_set_create");
  }

  return copy;
}

ih_case_set_t *ih_case_set_create_from_difference(ih_case_set_t *set_a,
    ih_case_set_t *set_b)
{
  assert(set_a);
  assert(set_b);
  ih_case_set_t *difference;

  difference = ih_case_set_copy(set_a);
  if (difference) {
    if (!ih_case_set_expunge(difference, set_b)) {
      ih_core_trace("x_case_set_expunge");
      ih_case_set_destroy(difference);
      difference = NULL;
    }
  } else {
    ih_core_trace("x_case_set_copy");
  }

  return difference;
}

ih_case_set_t *ih_case_set_create_from_message
(ih_core_iobject_t *iobject, ih_core_message_t *message,
    ih_core_message_create_from_message_f create_from_message)
{
  assert(iobject);
  assert(message);
  assert(create_from_message);
  ih_case_set_t *set;
  long set_size;
  long each_object;
  void *object;

  set = ih_case_set_create(iobject);
  if (set) {
    set_size = ih_core_message_take_long_value(message);
    for (each_object = 0; each_object < set_size; each_object++) {
      object = create_from_message(message);
      if (!ih_case_set_add(set, object)) {
        ih_core_trace("x_case_set_add");
      }
    }
  } else {
    ih_core_trace("x_case_set_create");
  }

  return set;
}

ih_case_set_t *ih_case_set_create_from_union(ih_case_set_t *set_a,
    ih_case_set_t *set_b)
{
  assert(set_a);
  assert(set_b);
  ih_case_set_t *union_set;
  void *object;

  union_set = ih_case_set_copy(set_a);
  if (union_set) {
    ih_case_set_iterate_start(set_b);
    while ((object = ih_case_set_iterate_next(set_b))) {
      ih_case_set_add(union_set, object);
    }
  } else {
    ih_core_trace("x_case_set_copy");
  }

  return union_set;
}

void ih_case_set_dont_destroy_objects(ih_case_set_t *set)
{
  ih_case_set_get_iobject(set)->destroy = NULL;
}

ih_core_bool_t ih_case_set_expunge(ih_case_set_t *set,
    ih_case_set_t *expunge_these)
{
  assert(set);
  assert(expunge_these);
  ih_core_bool_t success;
  void *object;

  ih_case_set_iterate_start(expunge_these);
  while ((object = ih_case_set_iterate_next(expunge_these))) {
    ih_case_set_remove(set, object);
  }

  /*
    TODO: return codes in ih_core_set interface don't allow us to determine
    success or failure here
  */
  success = ih_core_bool_true;

  return success;
}

void *ih_case_set_find_copy(ih_case_set_t *set, void *decoy_object)
{
  void *found_object;
  void *found_object_copy;

  found_object = ih_case_set_find(set, decoy_object);
  if (found_object) {
    found_object_copy = ih_case_set_get_iobject(set)->copy(found_object);
    if (!found_object_copy) {
      ih_core_trace("copy");
    }
  } else {
    found_object_copy = NULL;
  }

  return found_object_copy;
}

void *ih_case_set_find_take(ih_case_set_t *set,
    void *decoy_object)
{
  void *object;

  object = ih_case_set_find(set, decoy_object);
  if (object) {
    if (!ih_case_set_remove(set, decoy_object)) {
      ih_core_trace("x_case_set_remove");
    }
  }

  return object;
}

ih_case_array_t *ih_case_set_get_as_array(ih_case_set_t *set)
{
  assert(set);
  ih_case_array_t *array;
  void *object;
  unsigned long object_count;
  unsigned long object_index;
  ih_core_iobject_t *iobject = ih_case_set_get_iobject(set);

  object_count = ih_case_set_get_size(set);

  array = ih_case_array_create(object_count, iobject->compare,
      iobject->copy, IH_CORE_OBJECT_NO_DESTROY_F);
  if (array) {
    object_index = 0;
    ih_case_set_iterate_start(set);
    while ((object = ih_case_set_iterate_next(set))) {
      ih_case_array_add(array, object_index, object);
      object_index++;
    }
  } else {
    ih_core_trace("x_case_array_create");
  }

  return array;
}

ih_case_list_t *ih_case_set_get_as_list(ih_case_set_t *set)
{
  assert(set);
  ih_case_list_t *list;
  void *object;
  ih_core_iobject_t *iobject = ih_case_set_get_iobject(set);

  list = ih_case_list_create(iobject->compare, iobject->copy,
      IH_CORE_OBJECT_NO_DESTROY_F);
  if (list) {
    ih_case_set_iterate_start(set);
    while ((object = ih_case_set_iterate_next(set))) {
      ih_case_list_add_last(list, object);
    }
  } else {
    ih_core_trace("x_case_list_create");
  }

  return list;
}

char *ih_case_set_get_as_delimited_string(ih_case_set_t *set,
    ih_core_object_get_as_string_f get_as_string, const char *delimiter)
{
  assert(set);
  assert(get_as_string);
  assert(delimiter);
  char *string;
  void *object;
  char *object_string;
  unsigned long object_index;
  unsigned long last_object_index;
  ih_core_bool_t success;

  string = NULL;
  last_object_index = ih_case_set_get_size(set) - 1;
  success = ih_core_bool_true;

  object_index = 0;
  ih_case_set_iterate_start(set);
  while ((object = ih_case_set_iterate_next(set))) {
    object_string = get_as_string(object);
    if (object_string) {
      string = ih_core_string_append(string, object_string);
      free(object_string);
      if (string) {
        if (object_index != last_object_index) {
          string = ih_core_string_append(string, delimiter);
          if (!string) {
            success = ih_core_bool_false;
            ih_core_trace("x_core_string_append");
            break;
          }
        }
      } else {
        success = ih_core_bool_false;
        ih_core_trace("x_core_string_append");
        break;
      }
    } else {
      success = ih_core_bool_false;
      ih_core_trace("get_as_string");
      break;
    }
    object_index++;
  }

  if (!success && string) {
    free(string);
    string = NULL;
  }

  return string;
}

void ih_case_set_init_iobject(ih_core_iobject_t *iobject)
{
  ih_core_iobject_init(iobject, ih_case_set_compare, NULL, ih_case_set_copy,
      ih_case_set_destroy, NULL, NULL);
}

ih_core_bool_t ih_case_set_overlaps(ih_case_set_t *set_a,
    ih_case_set_t *set_b)
{
  assert(set_a);
  assert(set_b);
  ih_core_bool_t overlaps;
  void *object;
  unsigned long set_a_size;
  unsigned long set_b_size;
  ih_case_set_t *larger_set;
  ih_case_set_t *smaller_set;

  set_a_size = ih_case_set_get_size(set_a);
  set_b_size = ih_case_set_get_size(set_b);
  if (set_a_size > set_b_size) {
    larger_set = set_a;
    smaller_set = set_b;
  } else {
    larger_set = set_b;
    smaller_set = set_a;
  }

  overlaps = ih_core_bool_false;
  ih_case_set_iterate_start(smaller_set);
  while ((object = ih_case_set_iterate_next(smaller_set))) {
    if (ih_case_set_find(larger_set, object)) {
      overlaps = ih_core_bool_true;
      break;
    }
  }

  return overlaps;
}
