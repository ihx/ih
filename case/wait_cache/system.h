#ifndef ih_case_wait_cache_system_h
#define ih_case_wait_cache_system_h

#include "ih/core/object.h"
#include "ih/core/uuid.h"

struct ih_case_wait_cache_system_t;
typedef struct ih_case_wait_cache_system_t ih_case_wait_cache_system_t;

ih_core_bool_t ih_case_wait_cache_system_add
(ih_case_wait_cache_system_t *system, ih_core_uuid_t *object_uuid,
    void *object, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, unsigned long lifetime_seconds);

void ih_case_wait_cache_system_clear(ih_case_wait_cache_system_t *system);

ih_case_wait_cache_system_t *ih_case_wait_cache_system_create();

void ih_case_wait_cache_system_destroy
(ih_case_wait_cache_system_t *system);

void *ih_case_wait_cache_system_find_wait_copy_expire
(ih_case_wait_cache_system_t *system, ih_core_uuid_t *object_uuid,
    unsigned long max_wait_seconds);

unsigned long ih_case_wait_cache_system_get_size
(ih_case_wait_cache_system_t *system);

void ih_case_wait_cache_system_remove_objects
(ih_case_wait_cache_system_t *system);

#endif
