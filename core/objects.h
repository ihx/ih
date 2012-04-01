#ifndef ih_core_objects_h
#define ih_core_objects_h

#include "ih/core/iobject.h"

struct ih_core_objects_t {
  ih_core_iobject_t long_iobject;
  ih_core_iobject_t pair_iobject;
  ih_core_iobject_t string_iobject;
  ih_core_iobject_t unsigned_long_iobject;
  ih_core_iobject_t uuid_iobject;
  ih_core_iobject_t void_iobject;
};
typedef struct ih_core_objects_t ih_core_objects_t;

ih_core_objects_t ih_core_objects;

void ih_core_objects_init();

#endif
