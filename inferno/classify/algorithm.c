#include "ih/inferno/classify/algorithm.h"
#include "ih/core/tools.h"

ih_core_bool_t ih_inferno_classify_algorithm_get_from_string(char *string,
    ih_inferno_classify_algorithm_t *algorithm)
{
  assert(string);
  assert(algorithm);
  ih_core_bool_t success;

  if (0 == strcmp(string, "archetype")) {
    success = ih_core_bool_true;
    *algorithm = IH_INFERNO_CLASSIFY_ALGORITHM_ARCHETYPE;

  } else if (0 == strcmp(string, "...")) {
    success = ih_core_bool_true;
    *algorithm = IH_INFERNO_CLASSIFY_ALGORITHM_ARCHETYPE;

  } else {
    success = ih_core_bool_false;
  }

  return success;
}

char *ih_inferno_classify_algorithm_get_string(ih_inferno_classify_algorithm_t algorithm)
{
  char *string;

  switch (algorithm) {
    case IH_INFERNO_CLASSIFY_ALGORITHM_ARCHETYPE:
      string = "archetype";
      break;
    default:
      string = NULL;
      break;
  }

  return string;
}
