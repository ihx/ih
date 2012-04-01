#ifndef ih_case_dumpster_h
#define ih_case_dumpster_h

#include "ih/case/array.h"
#include "ih/case/list.h"
#include "ih/case/set.h"
#include "ih/core/iobject.h"

struct ih_case_dumpster_t;
typedef struct ih_case_dumpster_t ih_case_dumpster_t;

ih_core_bool_t ih_case_dumpster_add(ih_case_dumpster_t *dumpster,
    void *object);

ih_case_dumpster_t *ih_case_dumpster_create(ih_core_iobject_t *iobject);

void ih_case_dumpster_destroy(ih_case_dumpster_t *dumpster);

ih_core_bool_t ih_case_dumpster_take_objects_from_list
(ih_case_dumpster_t *dumpster, ih_case_list_t *list);

#endif
