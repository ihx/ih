#ifndef ih_inferno_morpinferno_system_h
#define ih_inferno_morpinferno_system_h

#include "ih/inferno/core/goal.h"
#include "ih/inferno/search/algorithm.h"
#include "ih/inferno/search/tools.h"
#include "ih/core/tools.h"

struct ih_inferno_morpinferno_system_t;
typedef struct ih_inferno_morpinferno_system_t ih_inferno_morpinferno_system_t;

ih_inferno_morpinferno_system_t *ih_inferno_morpinferno_system_create
(ih_inferno_core_score_solution_f score_solution, ih_inferno_core_goal_t goal,
    void *context, ih_case_array_t *initial_solutions, ih_core_log_t *log);

void ih_inferno_morpinferno_system_destroy
(ih_inferno_morpinferno_system_t *system);

ih_case_array_t *ih_inferno_morpinferno_system_get_solutions_copy
(ih_inferno_morpinferno_system_t *system, unsigned short max_solution_count);

void ih_inferno_morpinferno_system_search
(ih_inferno_morpinferno_system_t *system,
    unsigned long max_wall_time_microseconds);

#endif
