#ifndef ih_seq_sequence_h
#define ih_seq_sequence_h

#include "ih/case/list.h"

struct ih_seq_sequence_t;
typedef struct ih_seq_sequence_t ih_seq_sequence_t;

typedef ih_core_bool_t (*ih_seq_sequence_get_data_f)
(ih_seq_sequence_t *sequence);

ih_seq_sequence_t *ih_seq_sequence_create(char *subject,
    ih_seq_sequence_get_data_f get_data);

void ih_seq_sequence_destroy(ih_seq_sequence_t *sequence);

ih_core_bool_t ih_seq_sequence_get_data(ih_seq_sequence_t *sequence);

ih_core_bool_t ih_seq_sequence_get_data_from_nasdaq
(ih_seq_sequence_t *sequence);

ih_core_bool_t ih_seq_sequence_get_data_from_yahoo
(ih_seq_sequence_t *sequence);

ih_case_list_t *ih_seq_sequence_get_points_last_n
(ih_seq_sequence_t *sequence, unsigned long n);

ih_case_list_t *ih_seq_sequence_get_points_since_timestamp
(ih_seq_sequence_t *sequence, unsigned long timestamp);

/*  char *ih_seq_sequence_get_subject(ih_seq_sequence_t *sequence);  */

#endif
