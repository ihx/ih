#ifndef ih_inferno_archetype_system_h
#define ih_inferno_archetype_system_h

#include "ih/core/log.h"
#include "ih/case/array.h"
#include "ih/core/bitarray.h"
#include "ih/inferno/classify/iclassify.h"

struct ih_inferno_archetype_system_t;
typedef struct ih_inferno_archetype_system_t ih_inferno_archetype_system_t;

void *ih_inferno_archetype_system_create(ih_case_array_t *classified_objects,
    ih_core_log_t *log);

void ih_inferno_archetype_system_destroy(void *system_void);

ih_core_bit_t ih_inferno_archetype_system_classify_object(void *system_void,
    ih_core_bitarray_t *object);

void ih_inferno_archetype_system_init_iclassify
(ih_inferno_classify_iclassify_t *iclassify);

ih_core_bool_t ih_inferno_archetype_system_learn(void *system_void);

ih_core_bool_t ih_inferno_archetype_system_observe_object(void *system_void,
    ih_core_bitarray_t *classified_object);

#endif
