#include "ih/core/basic/void.h"
#include "ih/core/tools.h"

int ih_core_basic_void_compare(void *object_a, void *object_b)
{
  int compare;

  if (object_a > object_b) {
    compare = 1;
  } else if (object_a < object_b) {
    compare = -1;
  } else {
    compare = 0;
  }

  return compare;
}

void *ih_core_basic_void_copy(void *object)
{
  return object;
}

void ih_core_basic_void_destroy(void *object)
{
  free(object);
}

char *ih_core_basic_void_get_as_string(void *object)
{
  ih_core_trace_exit("TODO: implement/test");

  assert(object);
  char *string;

  string = malloc(10 + 1);
  if (string) {
    snprintf(string, 10 + 1, "%p", object);
  } else {
    ih_core_trace_exit("malloc");
  }

  return string;
}

void ih_core_basic_void_init_iobject(ih_core_iobject_t *iobject)
{
  assert(iobject);

  iobject->get_as_string = ih_core_basic_void_get_as_string;
  iobject->compare = ih_core_basic_void_compare;
  iobject->copy = ih_core_basic_void_copy;
  iobject->destroy = ih_core_basic_void_destroy;
}
