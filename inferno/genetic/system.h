#ifndef ih_inferno_genetic_system_h
#define ih_inferno_genetic_system_h

#include "ih/inferno/core/goal.h"
#include "ih/inferno/search/isearch.h"
#include "ih/inferno/search/tools.h"

struct ih_inferno_genetic_system_t;
typedef struct ih_inferno_genetic_system_t ih_inferno_genetic_system_t;

void *ih_inferno_genetic_system_create(ih_inferno_core_score_solution_f score_solution,
    ih_inferno_core_goal_t goal, void *context,
    ih_case_array_t *initial_solutions, ih_core_log_t *log);

void ih_inferno_genetic_system_destroy(void *system_object);

ih_case_array_t *ih_inferno_genetic_system_get_solutions_copy(void *system_object,
    unsigned short max_solution_count);

void ih_inferno_genetic_system_init_isearch(ih_inferno_search_isearch_t *isearch);

void ih_inferno_genetic_system_search(void *system_object);

#endif
