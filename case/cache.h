#ifndef ih_case_cache_h
#define ih_case_cache_h

#include "ih/core/object.h"
#include "ih/sync/qutex.h"

struct ih_case_cache_t;
typedef struct ih_case_cache_t ih_case_cache_t;

ih_core_bool_t ih_case_cache_add(ih_case_cache_t *cache, void *object);

void ih_case_cache_clear(ih_case_cache_t *cache);

ih_case_cache_t *ih_case_cache_create(ih_core_object_compare_f compare,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy,
    ih_core_object_evaluate_condition_f remove_condition);

void ih_case_cache_destroy(ih_case_cache_t *cache);

void *ih_case_cache_find(ih_case_cache_t *cache, void *object);

void *ih_case_cache_find_copy(ih_case_cache_t *cache, void *object);

unsigned long ih_case_cache_get_size(ih_case_cache_t *cache);

void ih_case_cache_remove_objects(ih_case_cache_t *cache);

#endif
