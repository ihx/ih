#include "ih/inferno/search/isearch.h"

void ih_inferno_search_isearch_init(ih_inferno_search_isearch_t *isearch,
    ih_inferno_search_isearch_create_f create, ih_inferno_search_isearch_destroy_f destroy,
    ih_inferno_search_isearch_get_solutions_copy_f get_solutions_copy,
    ih_inferno_search_isearch_search_f search)
{
  assert(isearch);

  isearch->create = create;
  isearch->destroy = destroy;
  isearch->get_solutions_copy = get_solutions_copy;
  isearch->search = search;
}
