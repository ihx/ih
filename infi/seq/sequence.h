#ifndef ih_infi_seq_sequence_h
#define ih_infi_seq_sequence_h

#include "ih/case/list.h"

struct ih_infi_seq_sequence_t;
typedef struct ih_infi_seq_sequence_t ih_infi_seq_sequence_t;

typedef ih_core_bool_t (*ih_infi_seq_sequence_get_data_f)
(ih_infi_seq_sequence_t *sequence);

ih_infi_seq_sequence_t *ih_infi_seq_sequence_create(char *subject,
    ih_infi_seq_sequence_get_data_f get_data);

void ih_infi_seq_sequence_destroy(ih_infi_seq_sequence_t *sequence);

ih_core_bool_t ih_infi_seq_sequence_get_data
(ih_infi_seq_sequence_t *sequence);

ih_core_bool_t ih_infi_seq_sequence_get_data_from_nasdaq
(ih_infi_seq_sequence_t *sequence);

ih_core_bool_t ih_infi_seq_sequence_get_data_from_random
(ih_infi_seq_sequence_t *sequence);

ih_core_bool_t ih_infi_seq_sequence_get_data_from_yahoo
(ih_infi_seq_sequence_t *sequence);

ih_case_list_t *ih_infi_seq_sequence_get_points_last_n_copy
(ih_infi_seq_sequence_t *sequence, unsigned long n);

ih_case_list_t *ih_infi_seq_sequence_get_points_since_timestamp_copy
(ih_infi_seq_sequence_t *sequence, unsigned long timestamp);

#endif
