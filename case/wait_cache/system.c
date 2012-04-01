#include "ih/case/cache.h"
#include "ih/core/tools.h"
#include "ih/case/wait_cache/item.h"
#include "ih/case/wait_cache/system.h"

#define WAIT_ON_OBJECT_SLEEP_MICROSECONDS IH_CORE_STANDARD_SLEEP_MICROSECONDS

struct ih_case_wait_cache_system_t {
  ih_case_cache_t *container_cache;
  pthread_mutex_t mutex;
};

static void *find_copy_expire(ih_case_wait_cache_system_t *system,
    ih_core_uuid_t *object_uuid);

void *find_copy_expire(ih_case_wait_cache_system_t *system,
    ih_core_uuid_t *object_uuid)
{
  assert(system);
  assert(object_uuid);
  ih_case_wait_cache_item_t *item_decoy;
  ih_case_wait_cache_item_t *item;
  void *object_copy;

  object_copy = NULL;

  item_decoy = ih_case_wait_cache_item_create_decoy(object_uuid);
  if (item_decoy) {

    pthread_mutex_lock(&system->mutex);
    {
      item = ih_case_cache_find(system->container_cache, item_decoy);
      if (item) {
        object_copy = ih_case_wait_cache_item_get_object_copy(item);
        if (!object_copy) {
          ih_core_trace("x_wait_cache_item_get_object_copy");
        }
        ih_case_wait_cache_item_expire(item);
      }
    }
    pthread_mutex_unlock(&system->mutex);

    ih_case_wait_cache_item_destroy_decoy(item_decoy);
  } else {
    ih_core_trace("x_wait_cache_item_create_decoy");
  }

  return object_copy;
}

ih_core_bool_t ih_case_wait_cache_system_add
(ih_case_wait_cache_system_t *system, ih_core_uuid_t *object_uuid,
    void *object, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, unsigned long lifetime_seconds)
{
  assert(object_uuid);
  assert(object);
  assert(copy);
  ih_core_bool_t success;
  ih_case_wait_cache_item_t *item;

  success = ih_core_bool_false;

  item = ih_case_wait_cache_item_create(object_uuid, object, copy, destroy,
      lifetime_seconds);
  if (item) {
    success = ih_case_cache_add(system->container_cache, item);
    if (!success) {
      ih_case_wait_cache_item_destroy(item);
      ih_core_trace("x_case_cache_add");
    }
  } else {
    ih_core_trace("x_wait_cache_item_create");
  }

  return success;
}

void ih_case_wait_cache_system_clear(ih_case_wait_cache_system_t *system)
{
  ih_case_cache_clear(system->container_cache);
}

ih_case_wait_cache_system_t *ih_case_wait_cache_system_create()
{
  ih_case_wait_cache_system_t *system;
  ih_core_bool_t so_far_so_good;
  ih_core_bool_t mutex_needs_destroy;

  mutex_needs_destroy = ih_core_bool_false;

  system = malloc(sizeof *system);
  if (system) {
    system->container_cache = ih_case_cache_create
      (ih_case_wait_cache_item_compare, ih_case_wait_cache_item_copy,
          ih_case_wait_cache_item_destroy,
          ih_case_wait_cache_item_is_expired);
    if (system->container_cache) {
      so_far_so_good = ih_core_bool_true;
    } else {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("new");
    }
  } else {
    so_far_so_good = ih_core_bool_false;
    ih_core_trace("malloc");
  }

  if (so_far_so_good) {
    if (0 == pthread_mutex_init(&system->mutex, NULL)) {
      mutex_needs_destroy = ih_core_bool_true;
    } else {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("pthread_mutex_init");
    }
  }

  if (system && !so_far_so_good) {
    if (system->container_cache) {
      ih_case_cache_destroy(system->container_cache);
    }
    if (mutex_needs_destroy) {
      if (0 != pthread_mutex_destroy(&system->mutex)) {
        ih_core_trace("pthread_mutex_destroy");
      }
    }
    free(system);
    system = NULL;
  }

  return system;
}

void ih_case_wait_cache_system_destroy(ih_case_wait_cache_system_t *system)
{
  assert(system);
  ih_case_cache_destroy(system->container_cache);
  if (0 != pthread_mutex_destroy(&system->mutex)) {
    ih_core_trace("pthread_mutex_destroy");
  }
  free(system);
}

void *ih_case_wait_cache_system_find_wait_copy_expire
(ih_case_wait_cache_system_t *system, ih_core_uuid_t *object_uuid,
    unsigned long max_wait_seconds)
{
  assert(system);
  assert(object_uuid);
  void *object_copy;
  time_t start_wait_time;
  time_t current_time;
  unsigned long wait_time_seconds;

  start_wait_time = time(NULL);

  do {
    object_copy = find_copy_expire(system, object_uuid);
    if (!object_copy) {
      usleep(WAIT_ON_OBJECT_SLEEP_MICROSECONDS);
      current_time = time(NULL);
      wait_time_seconds = current_time - start_wait_time;
    }
  } while (!object_copy && (wait_time_seconds < max_wait_seconds));

  return object_copy;
}

unsigned long ih_case_wait_cache_system_get_size
(ih_case_wait_cache_system_t *system)
{
  return ih_case_cache_get_size(system->container_cache);
}

void ih_case_wait_cache_system_remove_objects
(ih_case_wait_cache_system_t *system)
{
  pthread_mutex_lock(&system->mutex);
  ih_case_cache_remove_objects(system->container_cache);
  pthread_mutex_unlock(&system->mutex);
}
