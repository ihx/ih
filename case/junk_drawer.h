#ifndef ih_case_junk_drawer_h
#define ih_case_junk_drawer_h

#include "ih/core/object.h"
#include "ih/core/iobject.h"
#include "ih/core/tools.h"

struct ih_case_junk_drawer_t;
typedef struct ih_case_junk_drawer_t ih_case_junk_drawer_t;

ih_core_bool_t ih_case_junk_drawer_add
(ih_case_junk_drawer_t *junk_drawer, void *object);

void ih_case_junk_drawer_clear(ih_case_junk_drawer_t *junk_drawer);

ih_case_junk_drawer_t *ih_case_junk_drawer_create
(ih_core_iobject_t *iobject);

void ih_case_junk_drawer_destroy(ih_case_junk_drawer_t *junk_drawer);

void ih_case_junk_drawer_dont_destroy_objects
(ih_case_junk_drawer_t *junk_drawer);

void *ih_case_junk_drawer_find(ih_case_junk_drawer_t *junk_drawer,
    void *decoy_object);

ih_core_iobject_t *ih_case_junk_drawer_get_iobject
(ih_case_junk_drawer_t *junk_drawer);

unsigned long ih_case_junk_drawer_get_size
(ih_case_junk_drawer_t *junk_drawer);

void ih_case_junk_drawer_iterate_remove
(ih_case_junk_drawer_t *junk_drawer);

void ih_case_junk_drawer_iterate_start(ih_case_junk_drawer_t *junk_drawer);

void *ih_case_junk_drawer_iterate_next(ih_case_junk_drawer_t *junk_drawer);

ih_core_bool_t ih_case_junk_drawer_remove
(ih_case_junk_drawer_t *junk_drawer, void *decoy_object);

#endif
