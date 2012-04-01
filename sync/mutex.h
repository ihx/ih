#ifndef ih_sync_mutex_h
#define ih_sync_mutex_h

#include "ih/core/bool.h"

struct ih_sync_mutex_t;
typedef struct ih_sync_mutex_t ih_sync_mutex_t;

ih_sync_mutex_t *ih_sync_mutex_create();

void ih_sync_mutex_destroy(ih_sync_mutex_t *mutex);

void ih_sync_mutex_lock(ih_sync_mutex_t *mutex);

ih_core_bool_t ih_sync_mutex_trylock(ih_sync_mutex_t *mutex);

void ih_sync_mutex_unlock(ih_sync_mutex_t *mutex);

#endif
