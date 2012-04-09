#ifndef ih_case_mbin_h
#define ih_case_mbin_h

#include "ih/core/object.h"
#include "ih/core/iobject.h"
#include "ih/core/tools.h"

enum ih_case_mbin_set_type_t {
  IH_CASE_MBIN_SET_TYPE_MULTISET,
  IH_CASE_MBIN_SET_TYPE_SET
};
typedef enum ih_case_mbin_set_type_t ih_case_mbin_set_type_t;

struct ih_case_mbin_t;
typedef struct ih_case_mbin_t ih_case_mbin_t;

ih_core_bool_t ih_case_mbin_add(ih_case_mbin_t *mbin, void *object);

void ih_case_mbin_clear(ih_case_mbin_t *mbin);

ih_case_mbin_t *ih_case_mbin_create(ih_core_iobject_t *iobject,
    ih_case_mbin_set_type_t set_type);

void ih_case_mbin_destroy(ih_case_mbin_t *mbin);

void ih_case_mbin_dont_destroy_objects(ih_case_mbin_t *mbin);

void *ih_case_mbin_find(ih_case_mbin_t *mbin, void *decoy_object);

ih_core_iobject_t *ih_case_mbin_get_iobject(ih_case_mbin_t *mbin);

unsigned long ih_case_mbin_get_size(ih_case_mbin_t *mbin);

void ih_case_mbin_iterate_remove(ih_case_mbin_t *mbin);

void ih_case_mbin_iterate_start(ih_case_mbin_t *mbin);

void *ih_case_mbin_iterate_next(ih_case_mbin_t *mbin);

void ih_case_mbin_lock(ih_case_mbin_t *mbin);

ih_core_bool_t ih_case_mbin_remove(ih_case_mbin_t *mbin, void *decoy_object);

void ih_case_mbin_unlock(ih_case_mbin_t *mbin);

#endif
