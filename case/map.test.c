#include "ih/case/map.h"
#include "ih/core/basic/long.h"
#include "ih/core/objects.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"

int main(int argc, char *argv[])
{
  ih_case_map_t *map;

  ih_core_objects_init();

  char *a_left = "apple";
  unsigned long a_right = 0;

  char *b_left = "bear";
  unsigned long b_right = 1;

  unsigned long *ih_right;

  map = ih_case_map_create(&ih_core_objects.string_iobject,
      &ih_core_objects.long_iobject, IH_CASE_MAP_DONT_DESTROY);
  if (!map) {
    ih_core_trace_exit("x_case_map_create");
  }

  if (!ih_case_map_add(map, a_left, &a_right)) {
    ih_core_trace_exit("x_case_map_add");
  }

  if (!ih_case_map_add(map, b_left, &b_right)) {
    ih_core_trace_exit("x_case_map_add");
  }

  ih_case_map_print(map);

  ih_right = ih_case_map_find(map, b_left);
  if (ih_right) {
    printf(":%lu:\n", *ih_right);
  } else {
    ih_core_trace_exit("x_case_map_find");
  }

  ih_case_map_destroy(map);

  return 0;
}
