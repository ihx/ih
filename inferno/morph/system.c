#include "ih/inferno/morph/system.h"
#include "ih/inferno/search/system.h"
#include "ih/core/tools.h"

struct ih_inferno_morpinferno_system_t {
  ih_inferno_core_score_solution_f score_solution;
  ih_core_log_t *log;
  ih_inferno_search_system_t *search;
};

ih_inferno_morpinferno_system_t *ih_inferno_morpinferno_system_create
(ih_inferno_core_score_solution_f score_solution, ih_inferno_core_goal_t goal, void *context,
    ih_case_array_t *initial_solutions, ih_core_log_t *log)
{
  assert(score_solution);
  assert(log);
  ih_inferno_morpinferno_system_t *system;

  system = malloc(sizeof *system);
  if (system) {
    system->score_solution = score_solution;
    system->log = log;
    system->search = ih_inferno_search_system_create(score_solution, goal, context,
        initial_solutions, IH_INFERNO_SEARCH_ALGORITHM_COR3, log);
    if (!system->search) {
      ih_core_log_trace(log, "mrph", "inferno_search_system_create");
      free(system);
      system = NULL;
    }
  } else {
    ih_core_log_trace(log, "mrph", "malloc");
  }

  return system;
}

void ih_inferno_morpinferno_system_destroy(ih_inferno_morpinferno_system_t *system)
{
  assert(system);

  ih_inferno_search_system_destroy(system->search);
  free(system);
}

ih_case_array_t *ih_inferno_morpinferno_system_get_solutions_copy
(ih_inferno_morpinferno_system_t *system, unsigned short max_solution_count)
{
  assert(system);

  return ih_inferno_search_system_get_solutions_copy
    (system->search, max_solution_count);
}

void ih_inferno_morpinferno_system_search(ih_inferno_morpinferno_system_t *system,
    unsigned long max_wall_time_microseconds)
{
  assert(system);

  return ih_inferno_search_system_search(system->search, max_wall_time_microseconds);
}
