#include "ih/chage/tools.h"
#include "ih/core/tools.h"

ih_chage_interval_t ih_chage_determine_interval()
{
  return ih_core_get_microseconds() / IH_CHAGE_INTERVAL_MICROSECONDS;
}
