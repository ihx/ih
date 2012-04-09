int ih_core_uuid_compare(void *uuid_a_object, void *uuid_b_object)
{
  assert(uuid_a_object);
  assert(uuid_b_object);
  ih_core_uuid_t *uuid_a = uuid_a_object;
  ih_core_uuid_t *uuid_b = uuid_b_object;

  return uuid_compare(&uuid_a->uuid, &uuid_b->uuid, NULL);
}

void *ih_core_uuid_copy(void *uuid_object)
{
  assert(uuid_object);
  ih_core_uuid_t *original = uuid_object;
  ih_core_uuid_t *copy;
  uint32_t status;

  copy = malloc(sizeof *copy);
  if (copy) {
    copy->string = NULL;
    uuid_from_string(ih_core_uuid_get_string(original), &copy->uuid, &status);
    if (status != uuid_s_ok) {
      ih_core_trace("uuid_from_string");
    }
  } else {
    ih_core_trace("malloc");
  }

  return copy;
}

ih_core_uuid_t *ih_core_uuid_create()
{
  ih_core_uuid_t *uuid;
  uint32_t status;

  uuid = malloc(sizeof *uuid);
  if (uuid) {
    uuid_create(&uuid->uuid, &status);
    if (status != uuid_s_ok) {
      ih_core_trace("uuid_create");
    }
    uuid->string = NULL;
  } else {
    ih_core_trace("malloc");
  }

  return uuid;
}

ih_core_uuid_t *ih_core_uuid_create_from_string(const char *uuid_string)
{
  ih_core_uuid_t *uuid;
  uint32_t status;

  uuid = malloc(sizeof *uuid);
  if (uuid) {
    uuid->string = NULL;
    uuid_from_string(uuid_string, &uuid->uuid, &status);
    if (status != uuid_s_ok) {
      ih_core_trace("uuid_from_string");
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
  uint32_t status;

  uuid = uuid_object;

  if (!uuid->string) {
    uuid->string = malloc(37);
    if (uuid->string) {
      uuid_to_string(&uuid->uuid, &uuid->string, &status);
      if (status != uuid_s_ok) {
        ih_core_trace("uuid_to_string");
      }
    } else {
      uuid->string = NULL_UUID;
      ih_core_trace("malloc");
    }
  }

  assert(uuid->string);
  return uuid->string;
}
