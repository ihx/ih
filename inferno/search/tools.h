#ifndef ih_inferno_search_tools_h
#define ih_inferno_search_tools_h

#include "ih/case/array.h"
#include "ih/inferno/box/system.h"
#include "ih/inferno/core/iactor.h"
#include "ih/inferno/core/goal.h"

typedef void *(*ih_inferno_core_create_actor_f)(void *search_system,
    ih_core_bitarray_t *solution);

typedef void *(*ih_inferno_core_create_actor_random_f)(void *search_system);

typedef ih_core_bitarray_t *(*ih_inferno_core_get_solution_f)(void *object);

typedef ih_core_bool_t (*ih_inferno_core_score_solution_f)(void *context,
    ih_core_bitarray_t *solution, double *score);

ih_inferno_box_system_t *ih_inferno_core_create_actor_box(void *search_system,
    ih_inferno_box_coordinate_t *dimension_coordinate,
    ih_case_array_t *initial_solutions, ih_inferno_core_iactor_t *iactor,
    ih_core_log_t *log);

ih_case_array_t *ih_inferno_core_create_solutions_from_box
(ih_inferno_box_system_t *box, unsigned long max_solution_count,
    ih_inferno_core_get_solution_f get_solution,
    ih_inferno_core_score_solution_f score_solution,
    ih_inferno_core_goal_t goal, ih_core_object_compare_f compare_maximize,
    ih_core_object_compare_f compare_minimize,
    ih_core_object_copy_f copy_object, void *context, ih_core_log_t *log);

unsigned long ih_inferno_core_get_gene_start_address
(ih_core_bitarray_t *solution, unsigned long gene_index);

#endif
