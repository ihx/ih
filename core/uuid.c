#include "ih/core/bool.h"
#include "ih/core/tools.h"
#include "ih/core/uuid.h"

#define NULL_UUID "a8fffbb4-675c-4896-81f0-6eccf8bd8760"

struct ih_core_uuid_t {
  uuid_t uuid;
  char *string;
};

#if defined IH_PLATFORM_DARWIN
#include "ih/core/uuid.impl.darwin.c"
#elif defined IH_PLATFORM_LINUX
#include "ih/core/uuid.impl.linux.c"
#elif defined IH_PLATFORM_NETBSD
#include "ih/core/uuid.impl.netbsd.c"
#endif

ih_core_bool_t ih_core_uuid_add_to_message(void *uuid_object,
    ih_core_message_t *message)
{
  assert(uuid_object);
  assert(message);
  ih_core_bool_t success;
  char *uuid_string;
  ih_core_uuid_t *uuid;

  uuid = uuid_object;

  uuid_string = ih_core_uuid_get_string(uuid);
  if (ih_core_message_add_string(message, uuid_string)) {
    success = ih_core_bool_true;
  } else {
    success = ih_core_bool_false;
    ih_core_trace("x_core_message_add_string");
  }

  return success;
}

ih_core_bool_t ih_core_uuid_compare_equal(void *uuid_a_object,
    void *uuid_b_object)
{
  assert(uuid_a_object);
  assert(uuid_b_object);
  return (0 == ih_core_uuid_compare(uuid_a_object, uuid_b_object));
}

void *ih_core_uuid_create_from_message(ih_core_message_t *message)
{
  assert(message);
  ih_core_uuid_t *uuid;
  char *uuid_string;

  uuid_string = ih_core_message_take_string(message);
  if (uuid_string) {
    uuid = ih_core_uuid_create_from_string(uuid_string);
    if (!uuid) {
      ih_core_trace("x_core_uuid_create_from_string");
    }
    free(uuid_string);
  } else {
    ih_core_trace("x_core_message_take_string");
    uuid = NULL;
  }

  return uuid;
}

ih_core_uuid_t *ih_core_uuid_create_null()
{
  return ih_core_uuid_create_from_string(NULL_UUID);
}

void ih_core_uuid_destroy(void *uuid_object)
{
  assert(uuid_object);
  ih_core_uuid_t *uuid;

  uuid = uuid_object;

  if (uuid->string) {
    if (strcmp(uuid->string, NULL_UUID) != 0) {
      free(uuid->string);
    }
  }
  free(uuid);
}

char *ih_core_uuid_get_as_string(void *uuid_object)
{
  assert(uuid_object);
  char *s;

  s = strdup(ih_core_uuid_get_string(uuid_object));
  if (!s) {
    ih_core_trace("strdup");
  }

  return s;
}

unsigned long ih_core_uuid_get_memory_size_bytes(ih_core_uuid_t *uuid)
{
  assert(uuid);
  unsigned long size;

  size = sizeof *uuid;
  size += sizeof(uuid_t);

  return size;
}

unsigned long ih_core_uuid_hash(void *uuid_object)
{
  assert(uuid_object);
  ih_core_uuid_t *uuid = uuid_object;
  return ih_core_hash(ih_core_uuid_get_string(uuid));
}

void ih_core_uuid_init_iobject(ih_core_iobject_t *iobject)
{
  ih_core_iobject_init(iobject, ih_core_uuid_compare,
      ih_core_uuid_compare_equal, ih_core_uuid_copy,
      ih_core_uuid_destroy, ih_core_uuid_get_as_string,
      ih_core_uuid_hash);
}

ih_core_bool_t ih_core_uuid_is_null(ih_core_uuid_t *uuid)
{
  assert(uuid);
  ih_core_bool_t is_null;
  ih_core_uuid_t *null_uuid;

  is_null = ih_core_bool_false;

  null_uuid = ih_core_uuid_create_null();
  if (null_uuid) {
    if (0 == ih_core_uuid_compare(uuid, null_uuid)) {
      is_null = ih_core_bool_true;
    }
    ih_core_uuid_destroy(null_uuid);
  } else {
    ih_core_trace("x_core_uuid_create_null");
  }

  return is_null;
}
