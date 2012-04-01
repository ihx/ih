#include "ih/case/dumpster.h"
#include "ih/core/tools.h"

struct ih_case_dumpster_t {
  ih_core_iobject_t *iobject;
  ih_case_list_t *objects;
};

ih_core_bool_t ih_case_dumpster_add(ih_case_dumpster_t *dumpster,
    void *object)
{
  assert(dumpster);
  assert(object);
  ih_core_bool_t success;

  if (ih_case_list_add_last(dumpster->objects, object)) {
    success = ih_core_bool_true;
  } else {
    success = ih_core_bool_false;
  }

  return success;
}

ih_case_dumpster_t *ih_case_dumpster_create
(ih_core_iobject_t *iobject)
{
  assert(iobject);
  ih_case_dumpster_t *dumpster;

  dumpster = malloc(sizeof *dumpster);
  if (dumpster) {
    dumpster->iobject = iobject;
    dumpster->objects = ih_case_list_create(iobject->compare,
        iobject->copy, iobject->destroy);
    if (!dumpster->objects) {
      free(dumpster);
      dumpster = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return dumpster;
}

void ih_case_dumpster_destroy(ih_case_dumpster_t *dumpster)
{
  assert(dumpster);

  ih_case_list_destroy(dumpster->objects);
  free(dumpster);
}

ih_core_bool_t ih_case_dumpster_take_objects_from_list
(ih_case_dumpster_t *dumpster, ih_case_list_t *list)
{
  assert(dumpster);
  assert(list);
  ih_core_bool_t success;
  void *object;

  success = ih_core_bool_true;

  ih_case_list_dont_destroy_objects(list);
  ih_case_list_iterate_start(list);
  while ((object = ih_case_list_iterate_next(list))) {
    if (ih_case_dumpster_add(dumpster, object)) {
      ih_case_list_iterate_remove(list);
    } else {
      success = ih_core_bool_false;
      ih_core_trace("x_case_dumpster_add_object");
      break;
    }
  }

  return success;
}
