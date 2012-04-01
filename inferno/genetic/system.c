#include "ih/inferno/core/goal.h"
#include "ih/inferno/genetic/system.h"
#include "ih/inferno/search/isearch.h"
#include "ih/inferno/search/tools.h"
#include "ih/core/log.h"
#include "ih/case/array.h"

struct ih_inferno_genetic_system_t {
};

void *ih_inferno_genetic_system_create(ih_inferno_core_score_solution_f score_solution,
    ih_inferno_core_goal_t goal, void *context,
    ih_case_array_t *initial_solutions, ih_core_log_t *log)
{
  return NULL;
}

void ih_inferno_genetic_system_destroy(void *system_object)
{
}

ih_case_array_t *ih_inferno_genetic_system_get_solutions_copy(void *system_object,
    unsigned short max_solution_count)
{
  return NULL;
}

void ih_inferno_genetic_system_init_isearch(ih_inferno_search_isearch_t *isearch)
{
  ih_inferno_search_isearch_init(isearch, ih_inferno_genetic_system_create,
      ih_inferno_genetic_system_destroy, ih_inferno_genetic_system_get_solutions_copy,
      ih_inferno_genetic_system_search);
}

void ih_inferno_genetic_system_search(void *system_object)
{
}
