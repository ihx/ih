#include "ih/core/tools.h"

unsigned long ih_get_microseconds()
{
  struct timeval now;
  unsigned long microseconds;

  if (gettimeofday(&now, NULL) != -1) {
    microseconds = now.tv_usec;
  } else {
    ih_core_trace("gettimeofday");
    microseconds = 0;
  }

  return microseconds;
}
