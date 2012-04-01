#ifndef ih_inferno_memory_system_h
#define ih_inferno_memory_system_h

#include "ih/case/array.h"
#include "ih/core/bool.h"

struct ih_inferno_memory_system_t;
typedef struct ih_inferno_memory_system_t ih_inferno_memory_system_t;

ih_core_bool_t ih_inferno_memory_system_add(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary);

ih_inferno_memory_system_t *ih_inferno_memory_system_create(unsigned long size,
    unsigned short density);

void ih_inferno_memory_system_destroy(ih_inferno_memory_system_t *system);

ih_core_bool_t ih_inferno_memory_system_find(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary);

ih_case_array_t *ih_inferno_memory_system_find_cloud(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long cloud_size_max);

ih_core_bool_t ih_inferno_memory_system_remove(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary);

#endif
