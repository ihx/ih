#include "ih/core/standard.h"
#include "ih/infi/seq/response_get_last_n.h"

struct ih_infi_seq_response_get_last_n_t {
  ih_case_list_t *points;
};

ih_core_bool_t ih_infi_seq_response_get_last_n_add_to_message
(void *response_get_last_n_object, ih_core_message_t *message)
{
  return ih_core_bool_false;
}

ih_infi_seq_response_get_last_n_t *ih_infi_seq_response_get_last_n_create
(ih_case_list_t *points)
{
  return NULL;
}

ih_infi_seq_response_get_last_n_t *
ih_infi_seq_response_get_last_n_create_from_message
(ih_core_message_t *message)
{
  return NULL;
}

void ih_infi_seq_response_get_last_n_destroy
(ih_infi_seq_response_get_last_n_t *response_get_last_n)
{
  assert(response_get_last_n);
  assert(response_get_last_n->points);

  ih_case_list_destroy(response_get_last_n->points);
  free(response_get_last_n);
}

ih_case_list_t *ih_infi_seq_response_get_last_n_get_points
(ih_infi_seq_response_get_last_n_t *response_get_last_n)
{
  return response_get_last_n->points;
}
