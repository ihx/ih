#include "ih/core/basic/long.h"
#include "ih/core/message.h"
#include "ih/core/tools.h"

ih_core_bool_t ih_core_basic_long_add_to_message(void *long_object,
    ih_core_message_t *message)
{
  return ih_core_message_add_long(message, long_object);
}

int ih_core_basic_long_compare(void *long_a_object, void *long_b_object)
{
  long *long_a;
  long *long_b;
  int compare;

  long_a = long_a_object;
  long_b = long_b_object;

  if (*long_a > *long_b) {
    compare = 1;
  } else if (*long_a < *long_b) {
    compare = -1;
  } else {
    compare = 0;
  }

  return compare;
}

void *ih_core_basic_long_copy(void *long_object)
{
  assert(long_object);
  long *long_value;
  long *long_copy;

  long_value = long_object;
  long_copy = malloc(sizeof *long_copy);
  if (long_copy) {
    *long_copy = *long_value;
  } else {
    ih_core_trace("malloc");
  }

  return long_copy;
}

void *ih_core_basic_long_create_from_message(ih_core_message_t *message)
{
  return ih_core_message_take_long(message);
}

void ih_core_basic_long_destroy(void *long_object)
{
  assert(long_object);
  free(long_object);
}

ih_core_bool_t ih_core_basic_long_compare_equal(void *long_a_object, void *long_b_object)
{
  assert(long_a_object);
  assert(long_b_object);
  unsigned long *long_a = long_a_object;
  unsigned long *long_b = long_b_object;

  return *long_a == *long_b;
}

char *ih_core_basic_long_get_as_string(void *long_object)
{
  assert(long_object);
  long *long_value;
  char *string;

  long_value = long_object;

  if (-1 == asprintf(&string, "%li", *long_value)) {
    string = NULL;
  }

  return string;
}

unsigned long ih_core_basic_long_hash(void *long_object)
{
  assert(long_object);
  unsigned long *l = long_object;
  return *l;
}

void ih_core_basic_long_init_iobject(ih_core_iobject_t *iobject)
{
  assert(iobject);
  ih_core_iobject_init(iobject, ih_core_basic_long_compare,
      ih_core_basic_long_compare_equal, ih_core_basic_long_copy,
      ih_core_basic_long_destroy, ih_core_basic_long_get_as_string,
      ih_core_basic_long_hash);
}

void ih_core_basic_long_print(void *long_object)
{
  ih_core_object_print(long_object, ih_core_basic_long_get_as_string);
}
