#include "ih/case/set.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"
#include "ih/math/combination.h"

int main(int argc, char *argv[])
{
  ih_math_combination_t *combination;
  ih_case_set_t *set;
  ih_case_set_t *subset;
  ih_core_iobject_t set_iobject;

  ih_core_iobject_init(&set_iobject, ih_core_string_compare,
      ih_core_string_compare_equal, ih_core_string_copy,
      IH_CORE_OBJECT_NO_DESTROY_F, ih_core_string_get_as_string,
      ih_core_string_hash);
  set = ih_case_set_create(&set_iobject);
  if (!set) {
    ih_core_trace_exit("x_case_set_create");
  }

  ih_case_set_add(set, "rise");
  ih_case_set_add(set, "run");
  ih_case_set_add(set, "earth");
  ih_case_set_add(set, "sky");
  ih_case_set_add(set, "dot");
  ih_case_set_add(set, "oh");
  ih_case_set_add(set, "bird");
  ih_case_set_add(set, "fish");

  combination = ih_math_combination_create(set);
  if (!combination) {
    ih_core_trace_exit("x_math_combination_create");
  }

  ih_math_combination_iterate_start(combination);
  while ((subset = ih_math_combination_iterate_next(combination))) {
    ih_case_set_print(subset, ih_core_string_get_as_string);
    ih_case_set_destroy(subset);
  }

  ih_math_combination_destroy(combination);
  ih_case_set_destroy(set);

  return 0;
}
