#ifndef ih_core_basic_int_h
#define ih_core_basic_int_h

#include "ih/core/object.h"
#include "ih/core/iobject.h"

struct ih_core_basic_int_t;
typedef struct ih_core_basic_int_t ih_core_basic_int_t;

int ih_core_basic_int_compare(void *int_object_a, void *int_object_b);

void *ih_core_basic_int_copy(void *int_object);

ih_core_basic_int_t *ih_core_basic_int_create();

void ih_core_basic_int_destroy(void *int_object);

char *ih_core_basic_int_get_as_string(void *int_object);

void ih_core_basic_int_init_iobject(ih_core_iobject_t *iobject);

#endif
