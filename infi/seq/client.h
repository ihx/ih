#ifndef ih_infi_seq_client_h
#define ih_infi_seq_client_h

#include "ih/case/list.h"
#include "ih/core/standard.h"

struct ih_infi_seq_client_t;
typedef struct ih_infi_seq_client_t ih_infi_seq_client_t;

ih_infi_seq_client_t *ih_infi_seq_client_create();
void ih_infi_seq_client_destroy(ih_infi_seq_client_t *client);
ih_case_list_t *ih_infi_seq_client_get_last_n(ih_infi_seq_client_t *client);
ih_case_list_t *ih_infi_seq_client_get_since_timestamp
(ih_infi_seq_client_t *client);

#endif
