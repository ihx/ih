#ifndef ih_sync_qutex_h
#define ih_sync_qutex_h

#include "ih/core/bool.h"
#include "ih/sync/mutex.h"

struct ih_sync_qutex_t;
typedef struct ih_sync_qutex_t ih_sync_qutex_t;

ih_sync_qutex_t *ih_sync_qutex_create();

void ih_sync_qutex_destroy(ih_sync_qutex_t *qutex);

void ih_sync_qutex_lock_exclusive(ih_sync_qutex_t *qutex);

void ih_sync_qutex_lock_shared(ih_sync_qutex_t *qutex);

ih_core_bool_t ih_sync_qutex_trylock_exclusive(ih_sync_qutex_t *qutex);

ih_core_bool_t ih_sync_qutex_trylock_shared(ih_sync_qutex_t *qutex);

void ih_sync_qutex_unlock_exclusive(ih_sync_qutex_t *qutex);

void ih_sync_qutex_unlock_shared(ih_sync_qutex_t *qutex);

#endif
