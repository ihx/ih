#include "ih/case/set.h"
#include "ih/case/mbin.h"

ih_core_bool_t ih_case_set_add(ih_case_set_t *set, void *object)
{
  return ih_case_mbin_add((ih_case_mbin_t *) set, object);
}

ih_core_bool_t ih_case_set_add_replace(ih_case_set_t *set, void *object)
{
  return ih_core_bool_false;
}

ih_case_set_t *ih_case_set_create(ih_core_iobject_t *iobject)
{
  return (ih_case_set_t *) ih_case_mbin_create(iobject,
      IH_CASE_MBIN_SET_TYPE_SET);
}

void ih_case_set_destroy(void *set_object)
{
  ih_case_mbin_destroy(set_object);
}

void *ih_case_set_find(ih_case_set_t *set, void *decoy_object)
{
  return ih_case_mbin_find((ih_case_mbin_t *) set, decoy_object);
}

void *ih_case_set_find_any(ih_case_set_t *set)
{
  return NULL;
}

ih_core_iobject_t *ih_case_set_get_iobject(ih_case_set_t *set)
{
  return ih_case_mbin_get_iobject((ih_case_mbin_t *) set);
}

unsigned long ih_case_set_get_size(ih_case_set_t *set)
{
  return ih_case_mbin_get_size((ih_case_mbin_t *) set);
}

void *ih_case_set_iterate_next(ih_case_set_t *set)
{
  return ih_case_mbin_iterate_next((ih_case_mbin_t *) set);
}

void ih_case_set_iterate_remove(ih_case_set_t *set)
{
  ih_case_mbin_iterate_remove((ih_case_mbin_t *) set);
}

void ih_case_set_iterate_start(ih_case_set_t *set)
{
  ih_case_mbin_iterate_start((ih_case_mbin_t *) set);
}

void ih_case_set_print(ih_case_set_t *set,
    ih_core_object_get_as_string_f get_object_as_string)
{
  assert(set);
  assert(get_object_as_string);
  void *object;
  char *string;

  ih_case_set_iterate_start(set);
  while ((object = ih_case_set_iterate_next(set))) {
    string = get_object_as_string(object);
    if (string) {
      printf("%s,", string);
      free(string);
    } else {
      ih_core_trace("get_object_as_string");
    }
  }
  printf("\n");
}

ih_core_bool_t ih_case_set_remove(ih_case_set_t *set, void *object)
{
  ih_case_mbin_remove((ih_case_mbin_t *) set, object);
  return ih_core_bool_true;
}
