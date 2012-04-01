#ifndef ih_sync_run_h
#define ih_sync_run_h

#include "ih/core/bool.h"

enum ih_sync_run_style_t {
  ih_SYNC_RUN_STYLE_UNKNOWN,
  ih_SYNC_RUN_STYLE_ITERATIONS,
  ih_SYNC_RUN_STYLE_WALL_TIME,
  ih_SYNC_RUN_STYLE_GOAL_REACHED,
  ih_SYNC_RUN_STYLE_INFINITE
};
typedef enum ih_sync_run_style_t ih_sync_run_style_t;

struct ih_sync_run_t;
typedef struct ih_sync_run_t ih_sync_run_t;

void ih_sync_run_consider_goal_reached(ih_sync_run_t *run);

ih_sync_run_t *ih_sync_run_create(ih_sync_run_style_t run_style);

void ih_sync_run_destroy(ih_sync_run_t *run);

void ih_sync_run_increment_iterations(ih_sync_run_t *run);

ih_core_bool_t ih_sync_run_is_complete(ih_sync_run_t *run);

void ih_sync_run_reset(ih_sync_run_t *run);

void ih_sync_run_set_max_iterations(ih_sync_run_t *run,
    unsigned long max_iterations);

void ih_sync_run_set_wall_time_expiration_seconds(ih_sync_run_t *run,
    unsigned long seconds);

#endif
