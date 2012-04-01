#include "ih/case/map.h"
#include "ih/case/set.h"
#include "ih/core/pair.h"
#include "ih/core/tools.h"

struct ih_case_map_t {
  ih_case_set_t *pairs;
  ih_core_iobject_t *left_iobject;
  ih_core_iobject_t *right_iobject;
  ih_core_bool_t destroy;
  ih_core_iobject_t pairs_iobject;
};

ih_core_bool_t ih_case_map_add(ih_case_map_t *map, void *left,
    void *right)
{
  assert(map);
  assert(left);
  assert(right);
  ih_core_pair_t *pair;
  ih_core_bool_t success;

  pair = ih_core_pair_create(left, map->left_iobject, right,
      map->right_iobject, map->destroy);
  if (pair) {
    success = ih_core_bool_true;
    ih_case_set_add(map->pairs, pair);
  } else {
    success = ih_core_bool_false;
    ih_core_trace("x_core_pair_create");
  }

  return success;
}

int ih_case_map_compare(void *map_object_a, void *map_object_b)
{
  assert(map_object_a);
  assert(map_object_b);
  ih_case_map_t *map_a;
  ih_case_map_t *map_b;

  map_a = map_object_a;
  map_b = map_object_b;

  return ih_case_set_compare(map_a->pairs, map_b->pairs);
}

void *ih_case_map_copy(void *map_object)
{
  assert(map_object);
  ih_case_map_t *map;
  ih_case_map_t *map_copy;

  map = map_object;

  map_copy = ih_case_map_create(map->left_iobject, map->right_iobject,
      map->destroy);
  if (map_copy) {
    map_copy->pairs = ih_case_set_copy(map->pairs);
    if (!map_copy->pairs) {
      ih_core_trace("x_case_set_copy");
      free(map_copy);
      map_copy = NULL;
    }
  } else {
    ih_core_trace("x_case_map_create");
  }

  return map_copy;
}

ih_case_map_t *ih_case_map_create(ih_core_iobject_t *left_iobject,
    ih_core_iobject_t *right_iobject, ih_core_bool_t destroy)
{
  assert(left_iobject);
  assert(right_iobject);
  ih_case_map_t *map;

  map = malloc(sizeof *map);
  if (map) {
    map->left_iobject = left_iobject;
    map->right_iobject = right_iobject;
    map->destroy = destroy;
    ih_core_iobject_init(&map->pairs_iobject, ih_core_pair_compare_left,
        ih_core_pair_equal_left, ih_core_pair_copy, ih_core_pair_destroy,
        IH_CORE_OBJECT_NO_GET_AS_STRING_F, ih_core_pair_mod_left);
    map->pairs = ih_case_set_create(&map->pairs_iobject);
    if (!map->pairs) {
      ih_core_trace("x_case_set_create");
      free(map);
      map = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return map;
}

void ih_case_map_destroy(void *map_object)
{
  assert(map_object);
  ih_case_map_t *map;

  map = map_object;

  ih_case_set_destroy(map->pairs);
  free(map);
}

void *ih_case_map_find(ih_case_map_t *map,
    void *left_object_decoy)
{
  assert(map);
  assert(left_object_decoy);
  ih_core_pair_t *found_pair;
  void *found_object;
  ih_core_pair_t *pair_decoy;

  pair_decoy = ih_core_pair_create_decoy(left_object_decoy, map->left_iobject);
  if (pair_decoy) {
    found_pair = ih_case_set_find(map->pairs, pair_decoy);
    ih_core_pair_destroy_decoy(pair_decoy);
    if (found_pair) {
      found_object = ih_core_pair_get_right(found_pair);
    } else {
      found_object = NULL;
    }
  } else {
    found_object = NULL;
    ih_core_trace("pair_create_decoy");
  }

  return found_object;
}

void ih_case_map_print(ih_case_map_t *map)
{
  ih_case_set_print(map->pairs, ih_core_pair_get_as_string);
}

ih_core_bool_t ih_case_map_remove(ih_case_map_t *map,
    void *left_object_decoy)
{
  assert(map);
  assert(left_object_decoy);
  ih_core_bool_t success;
  ih_core_pair_t *pair_decoy;

  pair_decoy = ih_core_pair_create_decoy(left_object_decoy, map->left_iobject);
  if (pair_decoy) {
    success = ih_case_set_remove(map->pairs, pair_decoy);
  } else {
    success = ih_core_bool_false;
    ih_core_trace("pair_create_decoy");
  }

  return success;
}
