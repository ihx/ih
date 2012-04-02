#include "ih/core/standard.h"
#include "ih/infi/seq/request_get_since_timestamp.h"

struct ih_infi_seq_request_get_since_timestamp_t {
  char *subject;
  unsigned long timestamp;
};

ih_core_bool_t ih_infi_seq_request_get_since_timestamp_add_to_message
(void *request_get_since_timestamp_object, ih_core_message_t *message)
{
  return ih_core_bool_false;
}

ih_infi_seq_request_get_since_timestamp_t *
ih_infi_seq_request_get_since_timestamp_create
(char *subject, unsigned long timestamp)
{
  return NULL;
}

ih_infi_seq_request_get_since_timestamp_t *
ih_infi_seq_request_get_since_timestamp_create_from_message
(ih_core_message_t *message)
{
  return NULL;
}

void ih_infi_seq_request_get_since_timestamp_destroy
(ih_infi_seq_request_get_since_timestamp_t *request_get_since_timestamp)
{
  assert(request_get_since_timestamp);
  assert(request_get_since_timestamp->subject);

  free(request_get_since_timestamp->subject);
  free(request_get_since_timestamp);
}

char *ih_infi_seq_request_get_since_timestamp_get_subject
(ih_infi_seq_request_get_since_timestamp_t *request_get_since_timestamp)
{
  return request_get_since_timestamp->subject;
}

unsigned long ih_infi_seq_request_get_since_timestamp_get_timestamp
(ih_infi_seq_request_get_since_timestamp_t *request_get_since_timestamp)
{
  return request_get_since_timestamp->timestamp;
}
