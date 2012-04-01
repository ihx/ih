#ifndef ih_inferno_classify_algorithm_h
#define ih_inferno_classify_algorithm_h

#include "ih/core/bool.h"

enum ih_inferno_classify_algorithm_t {
  IH_INFERNO_CLASSIFY_ALGORITHM_ARCHETYPE,
};
typedef enum ih_inferno_classify_algorithm_t ih_inferno_classify_algorithm_t;

ih_core_bool_t ih_inferno_classify_algorithm_get_from_string(char *string,
    ih_inferno_classify_algorithm_t *algorithm);

char *ih_inferno_classify_algorithm_get_string
(ih_inferno_classify_algorithm_t algorithm);

#endif
