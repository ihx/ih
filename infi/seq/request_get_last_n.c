#include "ih/core/standard.h"
#include "ih/infi/seq/request_get_last_n.h"

struct ih_infi_seq_request_get_last_n_t {
  char *subject;
  unsigned long n;
};

ih_core_bool_t ih_infi_seq_request_get_last_n_add_to_message
(void *request_get_last_n_object, ih_core_message_t *message)
{
  return ih_core_bool_false;
}

ih_infi_seq_request_get_last_n_t *ih_infi_seq_request_get_last_n_create
(char *subject, unsigned long n)
{
  return NULL;
}

ih_infi_seq_request_get_last_n_t *
ih_infi_seq_request_get_last_n_create_from_message
(ih_core_message_t *message)
{
  return NULL;
}

void ih_infi_seq_request_get_last_n_destroy
(ih_infi_seq_request_get_last_n_t *request_get_last_n)
{
  assert(request_get_last_n);
  assert(request_get_last_n->subject);

  free(request_get_last_n->subject);
  free(request_get_last_n);
}

unsigned long ih_infi_seq_request_get_last_n_get_n
(ih_infi_seq_request_get_last_n_t *request_get_last_n)
{
  return request_get_last_n->n;
}

char *ih_infi_seq_request_get_last_n_get_subject
(ih_infi_seq_request_get_last_n_t *request_get_last_n)
{
  return request_get_last_n->subject;
}
