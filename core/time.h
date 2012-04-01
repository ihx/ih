#ifndef ih_core_time_h
#define ih_core_time_h

#include "ih/core/dayhour.h"

struct ih_core_time_t;
typedef struct ih_core_time_t ih_core_time_t;

ih_core_time_t *ih_core_time_create(unsigned long seconds);

void ih_core_time_destroy(ih_core_time_t *time);

void ih_core_time_get_dayhour(ih_core_time_t *time,
    ih_core_dayhour_t *dayhour);

#endif
