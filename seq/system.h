#ifndef ih_seq_system_h
#define ih_seq_system_h

#include "ih/core/log.h"
#include "ih/seq/sequence.h"

struct ih_seq_system_t;
typedef struct ih_seq_system_t ih_seq_system_t;

ih_core_bool_t ih_seq_system_add_sequence(ih_seq_system_t *system,
    char *subject, ih_seq_sequence_get_data_f get_data);

ih_seq_system_t *ih_seq_system_create(ih_core_log_t *log);

void ih_seq_system_destroy(ih_seq_system_t *system);

ih_case_list_t *ih_seq_system_get_last_n(ih_seq_system_t *system,
    char *subject, unsigned long n);

ih_case_list_t *ih_seq_system_get_since_timestamp(ih_seq_system_t *system,
    char *subject, unsigned long timestamp);

#endif
