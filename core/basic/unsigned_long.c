#include "ih/core/basic/unsigned_long.h"
#include "ih/core/tools.h"

int ih_core_basic_unsigned_long_compare(void *unsigned_long_a_object,
    void *unsigned_long_b_object)
{
  unsigned long *long_a;
  unsigned long *long_b;
  int compare;

  long_a = unsigned_long_a_object;
  long_b = unsigned_long_b_object;

  if (*long_a > *long_b) {
    compare = 1;
  } else if (*long_a < *long_b) {
    compare = -1;
  } else {
    compare = 0;
  }

  return compare;
}

ih_core_bool_t ih_core_basic_unsigned_long_compare_equal
(void *unsigned_long_a_object, void *unsigned_long_b_object)
{
  assert(unsigned_long_a_object);
  assert(unsigned_long_b_object);
  unsigned long *unsigned_long_a = unsigned_long_a_object;
  unsigned long *unsigned_long_b = unsigned_long_b_object;

  return *unsigned_long_a == *unsigned_long_b;
}

void *ih_core_basic_unsigned_long_copy(void *unsigned_long_object)
{
  assert(unsigned_long_object);
  unsigned long *long_value;
  unsigned long *long_copy;

  long_value = unsigned_long_object;
  long_copy = malloc(sizeof *long_copy);
  if (long_copy) {
    *long_copy = *long_value;
  } else {
    ih_core_trace("malloc");
  }

  return long_copy;
}

void ih_core_basic_unsigned_long_destroy(void *unsigned_long_object)
{
  free(unsigned_long_object);
}

char *ih_core_basic_unsigned_long_get_as_string(void *unsigned_long_object)
{
  assert(unsigned_long_object);
  unsigned long *unsigned_long;
  char *string;

  unsigned_long = unsigned_long_object;

  string = malloc(10 + 1);
  if (string) {
    snprintf(string, 10 + 1, "%lu", *unsigned_long);
  } else {
    ih_core_trace_exit("malloc");
  }

  return string;
}

unsigned long ih_core_basic_unsigned_long_hash(void *unsigned_long_object)
{
  assert(unsigned_long_object);
  unsigned long *unsigned_long = unsigned_long_object;
  return *unsigned_long;
}

void ih_core_basic_unsigned_long_init_iobject(ih_core_iobject_t *iobject)
{
  assert(iobject);
  ih_core_iobject_init(iobject, ih_core_basic_unsigned_long_compare,
      ih_core_basic_unsigned_long_compare_equal,
      ih_core_basic_unsigned_long_copy,
      ih_core_basic_unsigned_long_destroy,
      ih_core_basic_unsigned_long_get_as_string,
      ih_core_basic_unsigned_long_hash);
}
