#include "ih/core/tools.h"
#include "ih/case/wait_cache/item.h"

struct ih_case_wait_cache_item_t {
  time_t birth_time;
  unsigned long lifespan_seconds;
  ih_core_bool_t expired;
  ih_core_uuid_t *object_uuid;
  void *object;
  ih_core_object_copy_f copy;
  ih_core_object_destroy_f destroy;
};

int ih_case_wait_cache_item_compare(void *item_object_a,
    void *item_object_b)
{
  assert(item_object_a);
  assert(item_object_b);
  ih_case_wait_cache_item_t *item_a;
  ih_case_wait_cache_item_t *item_b;

  item_a = item_object_a;
  item_b = item_object_b;

  return ih_core_uuid_compare(item_a->object_uuid, item_b->object_uuid);
}

void *ih_case_wait_cache_item_copy(void *item_object)
{
  ih_core_trace_exit("TODO: implement");
}

ih_case_wait_cache_item_t *ih_case_wait_cache_item_create
(ih_core_uuid_t *object_uuid, void *object, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, unsigned long lifespan_seconds)
{
  assert(object_uuid);
  assert(object);
  assert(copy);
  ih_case_wait_cache_item_t *item;

  item = malloc(sizeof *item);
  if (item) {
    item->birth_time = time(NULL);
    item->object = object;
    item->copy = copy;
    item->destroy = destroy;
    item->lifespan_seconds = lifespan_seconds;
    item->expired = ih_core_bool_false;
    item->object_uuid = ih_core_uuid_copy(object_uuid);
    if (!item->object_uuid) {
      ih_core_trace("x_core_uuid_copy");
      free(item);
      item = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return item;
}

ih_case_wait_cache_item_t *ih_case_wait_cache_item_create_decoy
(ih_core_uuid_t *object_uuid)
{
  assert(object_uuid);
  ih_case_wait_cache_item_t *item;

  item = malloc(sizeof *item);
  if (item) {
    item->object_uuid = ih_core_uuid_copy(object_uuid);
    if (!item->object_uuid) {
      ih_core_trace("x_core_uuid_copy");
      free(item);
      item = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return item;
}

void ih_case_wait_cache_item_destroy(void *item_object)
{
  assert(item_object);
  ih_case_wait_cache_item_t *item;

  item = item_object;

  ih_core_uuid_destroy(item->object_uuid);
  if (item->destroy) {
    item->destroy(item->object);
  }
  free(item);
}

void ih_case_wait_cache_item_destroy_decoy(void *item_object)
{
  assert(item_object);
  ih_case_wait_cache_item_t *item;

  item = item_object;

  ih_core_uuid_destroy(item->object_uuid);
  free(item);
}

void ih_case_wait_cache_item_expire(ih_case_wait_cache_item_t *item)
{
  item->expired = ih_core_bool_true;
}

void *ih_case_wait_cache_item_get_object(ih_case_wait_cache_item_t *item)
{
  return item->object;
}

void *ih_case_wait_cache_item_get_object_copy
(ih_case_wait_cache_item_t *item)
{
  return item->copy(item->object);
}

ih_core_uuid_t *ih_case_wait_cache_item_get_object_uuid
(ih_case_wait_cache_item_t *item)
{
  return item->object_uuid;
}

ih_core_bool_t ih_case_wait_cache_item_is_expired(void *item_object)
{
  assert(item_object);
  ih_case_wait_cache_item_t *item;
  ih_core_bool_t is_expired;
  time_t now;

  item = item_object;

  if (item->expired) {
    is_expired = ih_core_bool_true;
  } else {
    now = time(NULL);
    if ((now - item->birth_time) > item->lifespan_seconds) {
      is_expired = ih_core_bool_true;
    } else {
      is_expired = ih_core_bool_false;
    }
  }

  return is_expired;
}
