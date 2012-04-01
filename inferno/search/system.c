#include "ih/inferno/bios/system.h"
#include "ih/inferno/cor3/system.h"
#include "ih/inferno/eos/system.h"
#include "ih/inferno/genetic/system.h"
#include "ih/inferno/search/isearch.h"
#include "ih/inferno/search/system.h"
#include "ih/core/tools.h"

struct ih_inferno_search_system_t {
  ih_inferno_search_isearch_t isearch;
  void *search_object;
};

static void init_isearch(ih_inferno_search_isearch_t *isearch,
    ih_inferno_search_algorithm_t algorithm);

ih_inferno_search_system_t *ih_inferno_search_system_create
(ih_inferno_core_score_solution_f score_solution, ih_inferno_core_goal_t goal, void *context,
    ih_case_array_t *initial_solutions, ih_inferno_search_algorithm_t algorithm,
    ih_core_log_t *log)
{
  assert(score_solution);
  assert(log);
  ih_inferno_search_system_t *search;

  search = malloc(sizeof *search);
  if (search) {
    init_isearch(&search->isearch, algorithm);
    search->search_object = search->isearch.create(score_solution, goal,
        context, initial_solutions, log);
    if (!search->search_object) {
      ih_core_trace("create");
      free(search);
      search = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return search;
}

void ih_inferno_search_system_destroy(ih_inferno_search_system_t *system)
{
  assert(system);
  system->isearch.destroy(system->search_object);
  free(system);
}

ih_case_array_t *ih_inferno_search_system_get_solutions_copy
(ih_inferno_search_system_t *system, unsigned short max_solution_count)
{
  assert(system);

#ifdef IH_INFERNO_BUILD_DEMO
  max_solution_count = ih_inferno_core_min(max_solution_count,
      IH_INFERNO_CORE_DEMO_SOLUTION_COUNT);
#endif

  return system->isearch.get_solutions_copy(system->search_object,
      max_solution_count);
}

void ih_inferno_search_system_search(ih_inferno_search_system_t *system,
    unsigned long max_wall_time_microseconds)
{
  assert(system);
  struct timeval start_time;

  gettimeofday(&start_time, NULL);

  do {
    system->isearch.search(system->search_object);
  } while (ih_core_time_is_remaining_microseconds
      (&start_time, max_wall_time_microseconds));
}

void init_isearch(ih_inferno_search_isearch_t *isearch,
    ih_inferno_search_algorithm_t algorithm)
{
  assert(isearch);

  switch (algorithm) {
    default:
    case IH_INFERNO_SEARCH_ALGORITHM_BIOS:
      ih_inferno_bios_system_init_isearch(isearch);
      break;
    case IH_INFERNO_SEARCH_ALGORITHM_COR3:
      ih_inferno_cor3_system_init_isearch(isearch);
      break;
    case IH_INFERNO_SEARCH_ALGORITHM_EOS:
      ih_inferno_eos_system_init_isearch(isearch);
      break;
    case IH_INFERNO_SEARCH_ALGORITHM_GENETIC:
      ih_inferno_genetic_system_init_isearch(isearch);
      break;
  }
}
