#ifndef ih_infi_seq_request_get_last_n_h
#define ih_infi_seq_request_get_last_n_h

#include "ih/core/bool.h"
#include "ih/core/message.h"

struct ih_infi_seq_request_get_last_n_t;
typedef struct ih_infi_seq_request_get_last_n_t
ih_infi_seq_request_get_last_n_t;

ih_core_bool_t ih_infi_seq_request_get_last_n_add_to_message
(void *request_get_last_n_object, ih_core_message_t *message);

ih_infi_seq_request_get_last_n_t *ih_infi_seq_request_get_last_n_create
(char *subject, unsigned long n);

ih_infi_seq_request_get_last_n_t *
ih_infi_seq_request_get_last_n_create_from_message
(ih_core_message_t *message);

void ih_infi_seq_request_get_last_n_destroy
(ih_infi_seq_request_get_last_n_t *request_get_last_n);

unsigned long ih_infi_seq_request_get_last_n_get_n
(ih_infi_seq_request_get_last_n_t *request_get_last_n);

char *ih_infi_seq_request_get_last_n_get_subject
(ih_infi_seq_request_get_last_n_t *request_get_last_n);

#endif
