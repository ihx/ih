#include "ih/inferno/bios/actor.h"
#include "ih/inferno/bios/constants.h"
#include "ih/inferno/bios/tools.h"
#include "ih/inferno/bios/system.h"
#include "ih/inferno/core/constants.h"

struct ih_inferno_bios_system_t {
  ih_inferno_box_system_t *box;
  ih_inferno_core_score_solution_f score_solution;
  ih_inferno_core_goal_t goal;
  ih_inferno_core_iactor_t iactor;
  void *context;
  ih_core_log_t *log;
};

void *ih_inferno_bios_system_create(ih_inferno_core_score_solution_f score_solution,
    ih_inferno_core_goal_t goal, void *context, ih_case_array_t *initial_solutions,
    ih_core_log_t *log)
{
  assert(score_solution);
  assert(log);
  ih_inferno_bios_system_t *system;
  ih_inferno_box_coordinate_t dimension_coordinate;

  system = malloc(sizeof *system);
  if (system) {
    system->score_solution = score_solution;
    system->goal = goal;
    system->context = context;
    system->log = log;
    ih_core_seed_random_with_time();
    ih_inferno_box_coordinate_init_with_xyz(&dimension_coordinate,
        IH_INFERNO_BIOS_BOX_DIMENSION, IH_INFERNO_BIOS_BOX_DIMENSION, 1);
    ih_inferno_bios_actor_init_iactor(&system->iactor);
    system->box = ih_inferno_core_create_actor_box(system, &dimension_coordinate,
        initial_solutions, &system->iactor, log);
    if (!system->box) {
      ih_core_log_trace(log, "bios", "inferno_core_create_actor_box");
      free(system);
      system = NULL;
    }

  } else {
    ih_core_log_trace(log, "bios", "malloc");
  }

  return system;
}

void ih_inferno_bios_system_destroy(void *system_object)
{
  assert(system_object);
  ih_inferno_bios_system_t *system;

  system = system_object;

  ih_inferno_box_system_destroy(system->box);
  free(system);
}

ih_inferno_box_system_t *ih_inferno_bios_system_get_box(ih_inferno_bios_system_t *system)
{
  return system->box;
}

void *ih_inferno_bios_system_get_context(ih_inferno_bios_system_t *system)
{
  return system->context;
}

ih_inferno_core_goal_t ih_inferno_bios_system_get_goal(ih_inferno_bios_system_t *system)
{
  return system->goal;
}

ih_core_log_t *ih_inferno_bios_system_get_log(ih_inferno_bios_system_t *system)
{
  return system->log;
}

ih_inferno_core_score_solution_f ih_inferno_bios_system_get_score_solution
(ih_inferno_bios_system_t *system)
{
  return system->score_solution;
}

ih_case_array_t *ih_inferno_bios_system_get_solutions_copy(void *system_object,
    unsigned short max_solution_count)
{
  assert(system_object);
  ih_inferno_bios_system_t *system;
  ih_case_array_t *solutions;

  system = system_object;

  solutions = ih_inferno_core_create_solutions_from_box(system->box,
      max_solution_count, ih_inferno_bios_actor_get_solution, system->score_solution,
      system->goal, ih_inferno_bios_actor_compare_maximize,
      ih_inferno_bios_actor_compare_minimize, ih_inferno_bios_actor_copy, system->context,
      system->log);
  if (!solutions) {
    ih_core_log_trace(system->log, "bios", "create_solutions_from_box");
  }

  return solutions;
}

void ih_inferno_bios_system_init_isearch(ih_inferno_search_isearch_t *isearch)
{
  ih_inferno_search_isearch_init(isearch, ih_inferno_bios_system_create,
      ih_inferno_bios_system_destroy, ih_inferno_bios_system_get_solutions_copy,
      ih_inferno_bios_system_search);
}

void ih_inferno_bios_system_search(void *system_object)
{
  assert(system_object);
  ih_inferno_bios_system_t *system;
  ih_inferno_bios_actor_t *actor;
  unsigned long i;

  system = system_object;

  for (i = 0; i < 32; i++) {
    actor = ih_inferno_box_system_find_random(system->box);
    ih_inferno_bios_actor_act(actor);
  }
}
