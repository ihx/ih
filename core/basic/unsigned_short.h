#ifndef ih_core_unsigned_short_h
#define ih_core_unsigned_short_h

#include "ih/core/object.h"

int ih_core_unsigned_short_compare(void *unsigned_short_a_object,
    void *unsigned_short_b_object);

void *ih_core_unsigned_short_copy(void *unsigned_short_object);

void ih_core_unsigned_short_destroy(void *unsigned_short_object);

void ih_core_unsigned_short_print(void *unsigned_short_object);

#endif
