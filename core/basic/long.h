#ifndef ih_core_basic_long_h
#define ih_core_basic_long_h

#include "ih/core/iobject.h"
#include "ih/core/object.h"

ih_core_bool_t ih_core_basic_long_add_to_message(void *long_object,
    ih_core_message_t *message);

int ih_core_basic_long_compare(void *long_a_object, void *long_b_object);

void *ih_core_basic_long_copy(void *long_object);

void *ih_core_basic_long_create_from_message(ih_core_message_t *message);

void ih_core_basic_long_destroy(void *long_object);

ih_core_bool_t ih_core_basic_long_compare_equal(void *long_a_object,
    void *long_b_object);

char *ih_core_basic_long_get_as_string(void *long_object);

unsigned long ih_core_basic_long_hash(void *long_object);

void ih_core_basic_long_init_iobject(ih_core_iobject_t *iobject);

void ih_core_basic_long_print(void *long_object);

#endif
