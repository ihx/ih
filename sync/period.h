#ifndef ih_sync_period_h
#define ih_sync_period_h

#include "ih/core/bool.h"

struct ih_sync_period_t;
typedef struct ih_sync_period_t ih_sync_period_t;

ih_sync_period_t *ih_sync_period_create(unsigned long seconds);

void ih_sync_period_destroy(ih_sync_period_t *period);

ih_core_bool_t ih_sync_period_once(ih_sync_period_t *period);

#endif
