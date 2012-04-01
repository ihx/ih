#ifndef ih_inferno_search_algorithm_h
#define ih_inferno_search_algorithm_h

#include "ih/core/bool.h"

enum ih_inferno_search_algorithm_t {
  IH_INFERNO_SEARCH_ALGORITHM_BIOS,
  IH_INFERNO_SEARCH_ALGORITHM_COR3,
  IH_INFERNO_SEARCH_ALGORITHM_EOS,
  IH_INFERNO_SEARCH_ALGORITHM_GENETIC,
};
typedef enum ih_inferno_search_algorithm_t ih_inferno_search_algorithm_t;

ih_core_bool_t ih_inferno_search_algorithm_get_from_string(char *string,
    ih_inferno_search_algorithm_t *algorithm);

char *ih_inferno_search_algorithm_get_string
(ih_inferno_search_algorithm_t algorithm);

#endif
