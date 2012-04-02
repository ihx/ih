#ifndef ih_ca_tools_h
#define ih_ca_tools_h

#include "ih/case/array.h"
#include "ih/core/bitarray.h"

typedef unsigned long (*ih_ca_select_initial_rule_f)();
typedef unsigned long (*ih_ca_select_initial_value_f)();

ih_case_array_t *ih_ca_create_initial_state(unsigned long cell_count,
    unsigned long time_steps, ih_ca_select_initial_rule_f select_initial_rule,
    ih_ca_select_initial_value_f select_initial_value);

ih_case_array_t *ih_ca_create_initial_state_from_bitarray
(ih_core_bitarray_t *bitarray);

ih_case_array_t *ih_ca_create_initial_state_salt_and_pepper_binary
(unsigned long cell_count, unsigned long time_steps);

ih_case_array_t *ih_ca_create_initial_state_single_cell_binary
(unsigned long cell_count, unsigned long time_steps);

ih_case_array_t *ih_ca_create_initial_state_single_cell_k3
(unsigned long cell_count);

unsigned long ih_ca_select_rule_0();

unsigned long ih_ca_select_value_0();

unsigned long ih_ca_select_value_salt_and_pepper();

#endif
