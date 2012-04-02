#ifndef ih_infi_seq_response_get_last_n_h
#define ih_infi_seq_response_get_last_n_h

#include "ih/case/list.h"
#include "ih/core/bool.h"
#include "ih/core/message.h"

struct ih_infi_seq_response_get_last_n_t;
typedef struct ih_infi_seq_response_get_last_n_t
ih_infi_seq_response_get_last_n_t;

ih_core_bool_t ih_infi_seq_response_get_last_n_add_to_message
(void *response_get_last_n_object, ih_core_message_t *message);

ih_infi_seq_response_get_last_n_t *ih_infi_seq_response_get_last_n_create
(ih_case_list_t *points);

ih_infi_seq_response_get_last_n_t *
ih_infi_seq_response_get_last_n_create_from_message
(ih_core_message_t *message);

void ih_infi_seq_response_get_last_n_destroy
(ih_infi_seq_response_get_last_n_t *response_get_last_n);

ih_case_list_t *ih_infi_seq_response_get_last_n_get_points
(ih_infi_seq_response_get_last_n_t *response_get_last_n);

#endif
