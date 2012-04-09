#ifndef ih_core_basic_unsigned_long_h
#define ih_core_basic_unsigned_long_h

#include "ih/core/iobject.h"

int ih_core_basic_unsigned_long_compare(void *unsigned_long_a_object,
    void *unsigned_long_b_object);

ih_core_bool_t ih_core_basic_unsigned_long_compare_equal
(void *unsigned_long_a_object, void *unsigned_long_b_object);

void *ih_core_basic_unsigned_long_copy(void *unsigned_long_object);

void ih_core_basic_unsigned_long_destroy(void *unsigned_long_object);

char *ih_core_basic_unsigned_long_get_as_string(void *unsigned_long_object);

unsigned long ih_core_basic_unsigned_long_hash(void *unsigned_long_object);

void ih_core_basic_unsigned_long_init_iobject
(ih_core_iobject_t *iobject);

#endif
