#ifndef ih_math_combination_h
#define ih_math_combination_h

#include "ih/case/set.h"

struct ih_math_combination_t;
typedef struct ih_math_combination_t ih_math_combination_t;

ih_math_combination_t *ih_math_combination_create(ih_case_set_t *set);

void ih_math_combination_destroy(ih_math_combination_t *combination);

ih_case_set_t *ih_math_combination_iterate_next
(ih_math_combination_t *combination);

void ih_math_combination_iterate_start(ih_math_combination_t *combination);

#endif
