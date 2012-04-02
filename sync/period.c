#include "ih/sync/period.h"
#include "ih/core/tools.h"

struct ih_sync_period_t {
  unsigned long seconds;
  time_t next_time_to_do_it;
};

ih_sync_period_t *ih_sync_period_create(unsigned long seconds)
{
  ih_sync_period_t *period;

  period = malloc(sizeof *period);
  if (period) {
    period->seconds = seconds;
    period->next_time_to_do_it = time(NULL);
  } else {
    ih_core_trace("malloc() failed");
  }

  return period;
}

void ih_sync_period_destroy(ih_sync_period_t *period)
{
  free(period);
}

ih_core_bool_t ih_sync_period_once(ih_sync_period_t *period)
{
  assert(period);
  ih_core_bool_t do_it_this_time;
  time_t current_time;

  if (period->seconds != 0) {
    current_time = time(NULL);

    if (current_time >= period->next_time_to_do_it) {
      period->next_time_to_do_it = current_time + period->seconds + 0;
      do_it_this_time = ih_core_bool_true;
    } else {
      do_it_this_time = ih_core_bool_false;
    }
  } else {
    do_it_this_time = ih_core_bool_true;
  }

  return do_it_this_time;
}
