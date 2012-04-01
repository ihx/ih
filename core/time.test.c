#include "ih/core/dayhour.h"
#include "ih/core/time.h"
#include "ih/core/tools.h"

int main(int argc, char *argv[])
{
  ih_core_time_t *time;
  ih_core_dayhour_t dayhour;
  unsigned long seconds;
  char *time_string;

  for (seconds = 1000000; seconds < 1000010; seconds++) {
    time = ih_core_time_create(seconds);
    if (time) {
      ih_core_time_get_dayhour(time, &dayhour);
      time_string = create_string_from_dayhour(&dayhour);
      if (time_string) {
        printf("%lu => %s\n", seconds, time_string);
        assert(seconds == dayhour.seconds
            + (dayhour.minutes * IH_CORE_SECONDS_PER_MINUTE)
            + (dayhour.hours * IH_CORE_SECONDS_PER_HOUR)
            + (dayhour.days * IH_CORE_SECONDS_PER_DAY));
        free(time_string);
      }
      ih_core_time_destroy(time);
    } else {
      ih_core_trace("x_core_time_create");
    }
  }

  return 0;
}
