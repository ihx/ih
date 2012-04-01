#include "ih/case/hasha.h"

struct ih_case_hasha_t {
};

ih_core_bool_t ih_case_hasha_add(ih_case_hasha_t *hasha, void *object)
{
  ih_core_implement();
  return ih_core_bool_false;
}

void ih_case_hasha_clear(ih_case_hasha_t *hasha)
{
  ih_core_implement();
}

ih_case_hasha_t *ih_case_hasha_create(ih_core_iobject_t *iobject)
{
  ih_core_implement();
  return NULL;
}

void ih_case_hasha_destroy(ih_case_hasha_t *hasha)
{
  ih_core_implement();
}

void ih_case_hasha_dont_destroy_objects(ih_case_hasha_t *hasha)
{
  ih_core_implement();
}

void *ih_case_hasha_find(ih_case_hasha_t *hasha, void *decoy_object)
{
  ih_core_implement();
  return NULL;
}

ih_core_iobject_t *ih_case_hasha_get_iobject(ih_case_hasha_t *hasha)
{
  ih_core_implement();
  return NULL;
}

unsigned long ih_case_hasha_get_size(ih_case_hasha_t *hasha)
{
  ih_core_implement();
  return 0;
}

void ih_case_hasha_iterate_remove(ih_case_hasha_t *hasha)
{
  ih_core_implement();
}

void ih_case_hasha_iterate_start(ih_case_hasha_t *hasha)
{
  ih_core_implement();
}

void *ih_case_hasha_iterate_next(ih_case_hasha_t *hasha)
{
  ih_core_implement();
  return NULL;
}

ih_core_bool_t ih_case_hasha_remove(ih_case_hasha_t *hasha,
    void *decoy_object)
{
  ih_core_implement();
  return ih_core_bool_false;
}
