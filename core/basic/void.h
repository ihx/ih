#ifndef ih_net_void_h
#define ih_net_void_h

#include "ih/core/iobject.h"

int ih_core_basic_void_compare(void *object_a, void *object_b);

void *ih_core_basic_void_copy(void *object);

void ih_core_basic_void_destroy(void *object);

char *ih_core_basic_void_get_as_string(void *object);

void ih_core_basic_void_init_iobject(ih_core_iobject_t *iobject);

#endif
