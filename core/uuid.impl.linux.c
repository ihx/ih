#include "ih/core/uuid.h"

int ih_core_uuid_compare(void *uuid_a_object, void *uuid_b_object)
{
  assert(uuid_a_object);
  assert(uuid_b_object);
  ih_core_uuid_t *uuid_a = uuid_a_object;
  ih_core_uuid_t *uuid_b = uuid_b_object;

  return uuid_compare(uuid_a->uuid, uuid_b->uuid);
}

/*
ih_core_bool_t ih_core_uuid_compare_equal(void *uuid_a_object, void *uuid_b_object)
{
  assert(uuid_a_object);
  assert(uuid_b_object);
  unsigned char *uuid_a = uuid_a_object;
  unsigned char *uuid_b = uuid_b_object;
  ih_core_bool_t equal = ih_core_bool_true;
  unsigned char i;

  for (i = 0; i < 16; i++) {
    if (*(uuid_a + i) != *(uuid_b + i)) {
      equal = ih_core_bool_false;
      break;
    }
  }

  return equal;
}
*/

void *ih_core_uuid_copy(void *uuid_object)
{
  assert(uuid_object);
  ih_core_uuid_t *original;
  ih_core_uuid_t *copy;

  original = uuid_object;

  copy = malloc(sizeof *copy);
  if (copy) {
    copy->string = NULL;
    uuid_copy(copy->uuid, original->uuid);
  } else {
    ih_core_trace("malloc");
  }

  return copy;
}

ih_core_uuid_t *ih_core_uuid_create()
{
  ih_core_uuid_t *uuid;

  uuid = malloc(sizeof *uuid);
  if (uuid) {
    uuid_generate(uuid->uuid);
    uuid->string = NULL;
  } else {
    ih_core_trace("malloc");
  }

  return uuid;
}

ih_core_uuid_t *ih_core_uuid_create_from_string(const char *uuid_string)
{
  ih_core_uuid_t *uuid;

  uuid = malloc(sizeof *uuid);
  if (uuid) {
    uuid->string = NULL;
    if (0 != uuid_parse(uuid_string, uuid->uuid)) {
      free(uuid);
      uuid = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return uuid;
}

char *ih_core_uuid_get_string(void *uuid_object)
{
  assert(uuid_object);
  ih_core_uuid_t *uuid;

  uuid = uuid_object;

  if (!uuid->string) {
    uuid->string = malloc(37);
    if (uuid->string) {
      uuid_unparse(uuid->uuid, uuid->string);
    } else {
      uuid->string = NULL_UUID;
      ih_core_trace("malloc");
    }
  }

  assert(uuid->string);
  return uuid->string;
}

unsigned long ih_core_uuid_hash(void *uuid_object, unsigned long divisor)
{
  assert(uuid_object);
  unsigned char *uuid = uuid_object;
  unsigned long dividend;
  unsigned long remainder;

  dividend = *((unsigned long *) (uuid + 12));
  remainder = dividend % divisor;
  /*  printf("%lu::%lu\n", dividend, remainder);  */

  return remainder;
}
