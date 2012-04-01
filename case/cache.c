#include "ih/case/cache.h"
#include "ih/case/set.h"
#include "ih/core/tools.h"

struct ih_case_cache_t {
  ih_case_set_t *objects;
  ih_sync_qutex_t *objects_qutex;
  ih_core_object_evaluate_condition_f remove_condition;
  ih_core_iobject_t objects_iobject;
};

ih_core_bool_t ih_case_cache_add(ih_case_cache_t *cache,
    void *object)
{
  assert(cache);
  assert(object);
  ih_core_bool_t success;

  ih_sync_qutex_lock_exclusive(cache->objects_qutex);
  success = ih_case_set_add(cache->objects, object);
  ih_sync_qutex_unlock_exclusive(cache->objects_qutex);

  if (!success) {
    ih_core_trace("x_case_set_add");
  }

  return success;
}

void ih_case_cache_clear(ih_case_cache_t *cache)
{
  ih_sync_qutex_lock_exclusive(cache->objects_qutex);
  ih_case_set_clear(cache->objects);
  ih_sync_qutex_unlock_exclusive(cache->objects_qutex);
}

ih_case_cache_t *ih_case_cache_create(ih_core_object_compare_f compare,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy,
    ih_core_object_evaluate_condition_f remove_condition)
{
  ih_case_cache_t *cache;
  ih_core_bool_t so_far_so_good;

  cache = malloc(sizeof *cache);
  if (cache) {
    cache->remove_condition = remove_condition;
    cache->objects_qutex = NULL;
    ih_core_iobject_init(&cache->objects_iobject, compare,
        IH_CORE_OBJECT_NO_COMPARE_EQUAL_F, copy, destroy,
        IH_CORE_OBJECT_NO_GET_AS_STRING_F, IH_CORE_OBJECT_NO_MOD_F);
    cache->objects = ih_case_set_create(&cache->objects_iobject);
    if (cache->objects) {
      so_far_so_good = ih_core_bool_true;
    } else {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("x_case_set_create");
    }
  } else {
    so_far_so_good = ih_core_bool_false;
    ih_core_trace("malloc() failed");
  }

  if (so_far_so_good) {
    cache->objects_qutex = ih_sync_qutex_create();
    if (!cache->objects_qutex) {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("x_core_qutex_create");
    }
  }

  if (!so_far_so_good) {
    if (cache->objects) {
      ih_case_set_destroy(cache->objects);
    }
    if (cache->objects_qutex) {
      ih_sync_qutex_destroy(cache->objects_qutex);
    }
    free(cache);
    cache = NULL;
  }

  return cache;
}

void ih_case_cache_destroy(ih_case_cache_t *cache)
{
  assert(cache);
  ih_case_set_destroy(cache->objects);
  ih_sync_qutex_destroy(cache->objects_qutex);
}

void *ih_case_cache_find(ih_case_cache_t *cache,
    void *object)
{
  assert(cache);
  assert(object);
  void *found_object;

  ih_sync_qutex_lock_shared(cache->objects_qutex);
  found_object = ih_case_set_find(cache->objects, object);
  ih_sync_qutex_unlock_shared(cache->objects_qutex);

  return found_object;
}

void *ih_case_cache_find_copy(ih_case_cache_t *cache,
    void *object)
{
  assert(cache);
  assert(object);
  void *object_copy;

  ih_sync_qutex_lock_shared(cache->objects_qutex);
  object_copy = ih_case_set_find_copy(cache->objects, object);
  ih_sync_qutex_unlock_shared(cache->objects_qutex);

  return object_copy;
}

unsigned long ih_case_cache_get_size(ih_case_cache_t *cache)
{
  assert(cache);
  unsigned long size;

  ih_sync_qutex_lock_shared(cache->objects_qutex);
  size = ih_case_set_get_size(cache->objects);
  ih_sync_qutex_unlock_shared(cache->objects_qutex);

  return size;
}

void ih_case_cache_remove_objects(ih_case_cache_t *cache)
{
  assert(cache);
  void *object;

  ih_sync_qutex_lock_shared(cache->objects_qutex);
  {
    ih_case_set_iterate_start(cache->objects);
    while ((object = ih_case_set_iterate_next(cache->objects))) {
      if (cache->remove_condition(object)) {
        ih_case_set_iterate_remove(cache->objects);
      }
    }
  }
  ih_sync_qutex_unlock_shared(cache->objects_qutex);
}
