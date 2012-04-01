#ifndef ih_core_basic_short_h
#define ih_core_basic_short_h

#include "ih/core/object.h"

ih_core_bool_t ih_core_basic_short_add_to_message(void *short_object,
    ih_core_message_t *message);

int ih_core_basic_short_compare(void *short_a_object, void *short_b_object);

void *ih_core_basic_short_copy(void *short_object);

void *ih_core_basic_short_take_from_message(ih_core_message_t *message);

void ih_core_basic_short_destroy(void *short_object);

void ih_core_basic_short_print(void *short_object);

#endif
