#ifndef ih_inferno_search_isearch_h
#define ih_inferno_search_isearch_h

#include "ih/inferno/core/goal.h"
#include "ih/inferno/search/tools.h"

typedef void * (*ih_inferno_search_isearch_create_f)
(ih_inferno_core_score_solution_f score_solution, ih_inferno_core_goal_t goal, void *context,
    ih_case_array_t *initial_solutions, ih_core_log_t *log);

typedef void (*ih_inferno_search_isearch_destroy_f)(void *search_object);

typedef ih_case_array_t * (*ih_inferno_search_isearch_get_solutions_copy_f)
  (void *search_object, unsigned short max_solution_count);

typedef void (*ih_inferno_search_isearch_search_f)(void *search_object);

struct ih_inferno_search_isearch_t {
  ih_inferno_search_isearch_create_f create;
  ih_inferno_search_isearch_destroy_f destroy;
  ih_inferno_search_isearch_get_solutions_copy_f get_solutions_copy;
  ih_inferno_search_isearch_search_f search;
};
typedef struct ih_inferno_search_isearch_t ih_inferno_search_isearch_t;

void ih_inferno_search_isearch_init(ih_inferno_search_isearch_t *isearch,
    ih_inferno_search_isearch_create_f create, ih_inferno_search_isearch_destroy_f destroy,
    ih_inferno_search_isearch_get_solutions_copy_f get_solutions_copy,
    ih_inferno_search_isearch_search_f search);

#endif
