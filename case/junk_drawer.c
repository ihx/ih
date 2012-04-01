#include "ih/case/junk_drawer.h"

/*
  super-simple
  great for small collections
  last-used stuff is near the top
  stochastic
  messy
  that's it
*/

struct ih_case_junk_drawer_t {
};

ih_core_bool_t ih_case_junk_drawer_add
(ih_case_junk_drawer_t *junk_drawer, void *object)
{
  return ih_core_bool_false;
}

void ih_case_junk_drawer_clear(ih_case_junk_drawer_t *junk_drawer)
{
}

ih_case_junk_drawer_t *ih_case_junk_drawer_create
(ih_core_iobject_t *iobject)
{
  return NULL;
}

void ih_case_junk_drawer_destroy(ih_case_junk_drawer_t *junk_drawer)
{
}

void ih_case_junk_drawer_dont_destroy_objects
(ih_case_junk_drawer_t *junk_drawer)
{
}

void *ih_case_junk_drawer_find(ih_case_junk_drawer_t *junk_drawer,
    void *decoy_object)
{
  return NULL;
}

ih_core_iobject_t *ih_case_junk_drawer_get_iobject
(ih_case_junk_drawer_t *junk_drawer)
{
  return NULL;
}

unsigned long ih_case_junk_drawer_get_size
(ih_case_junk_drawer_t *junk_drawer)
{
  return 0;
}

void ih_case_junk_drawer_iterate_remove(ih_case_junk_drawer_t *junk_drawer)
{
}

void ih_case_junk_drawer_iterate_start(ih_case_junk_drawer_t *junk_drawer)
{
}

void *ih_case_junk_drawer_iterate_next(ih_case_junk_drawer_t *junk_drawer)
{
  return NULL;
}

ih_core_bool_t ih_case_junk_drawer_remove
(ih_case_junk_drawer_t *junk_drawer, void *decoy_object)
{
  return ih_core_bool_false;
}
