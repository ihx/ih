#include "ih/core/standard.h"
#include "ih/infi/seq/response_get_since_timestamp.h"

struct ih_infi_seq_response_get_since_timestamp_t {
  ih_case_list_t *points;
};

ih_core_bool_t ih_infi_seq_response_get_since_timestamp_add_to_message
(void *response_get_since_timestamp_object, ih_core_message_t *message)
{
  return ih_core_bool_false;
}

ih_infi_seq_response_get_since_timestamp_t *
ih_infi_seq_response_get_since_timestamp_create(ih_case_list_t *points)
{
  return NULL;
}

ih_infi_seq_response_get_since_timestamp_t *
ih_infi_seq_response_get_since_timestamp_create_from_message
(ih_core_message_t *message)
{
  return NULL;
}

void ih_infi_seq_response_get_since_timestamp_destroy
(ih_infi_seq_response_get_since_timestamp_t *response_get_since_timestamp)
{
  assert(response_get_since_timestamp);
  assert(response_get_since_timestamp->points);

  ih_case_list_destroy(response_get_since_timestamp->points);
  free(response_get_since_timestamp);
}

ih_case_list_t *ih_infi_seq_response_get_since_timestamp_get_points
(ih_infi_seq_response_get_since_timestamp_t *response_get_since_timestamp)
{
  return response_get_since_timestamp->points;
}
