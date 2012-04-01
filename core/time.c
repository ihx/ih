#include "ih/core/time.h"
#include "ih/core/tools.h"

struct ih_core_time_t {
  unsigned long seconds;
};

ih_core_time_t *ih_core_time_create(unsigned long seconds)
{
  ih_core_time_t *time;

  time = malloc(sizeof *time);
  if (time) {
    time->seconds = seconds;
  } else {
    ih_core_trace("malloc");
  }

  return time;
}

void ih_core_time_destroy(ih_core_time_t *time)
{
  assert(time);
  free(time);
}

void ih_core_time_get_dayhour(ih_core_time_t *time,
    ih_core_dayhour_t *dayhour)
{
  assert(time);
  assert(dayhour);
  unsigned long seconds_left;

  seconds_left = time->seconds;

  dayhour->days = seconds_left / IH_CORE_SECONDS_PER_DAY;
  seconds_left -= (dayhour->days * IH_CORE_SECONDS_PER_DAY);

  dayhour->hours = seconds_left / IH_CORE_SECONDS_PER_HOUR;
  seconds_left -= (dayhour->hours * IH_CORE_SECONDS_PER_HOUR);

  dayhour->minutes = seconds_left / IH_CORE_SECONDS_PER_MINUTE;
  seconds_left -= (dayhour->minutes * IH_CORE_SECONDS_PER_MINUTE);

  dayhour->seconds = seconds_left;

}
