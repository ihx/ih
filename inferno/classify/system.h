#ifndef ih_inferno_classify_system_h
#define ih_inferno_classify_system_h

#include "ih/core/log.h"
#include "ih/case/array.h"
#include "ih/core/bit.h"
#include "ih/core/bitarray.h"
#include "ih/core/tools.h"
#include "ih/inferno/core/goal.h"
#include "ih/inferno/classify/algorithm.h"

struct ih_inferno_classify_system_t;
typedef struct ih_inferno_classify_system_t ih_inferno_classify_system_t;

ih_inferno_classify_system_t *ih_inferno_classify_system_create
(ih_case_array_t *classified_objects,
    ih_inferno_classify_algorithm_t algorithm, ih_core_log_t *log);

void ih_inferno_classify_system_destroy(ih_inferno_classify_system_t *system);

ih_core_bit_t ih_inferno_classify_system_classify_object
(ih_inferno_classify_system_t *system, ih_core_bitarray_t *object);

ih_case_array_t *ih_inferno_classify_system_classify_objects
(ih_inferno_classify_system_t *system, ih_case_array_t *objects);

ih_core_bool_t ih_inferno_classify_system_learn
(ih_inferno_classify_system_t *system,
    unsigned long max_wall_time_microseconds);

ih_core_bool_t ih_inferno_classify_system_observe_object
(ih_inferno_classify_system_t *system,
    ih_core_bitarray_t *classified_object);

ih_core_bool_t ih_inferno_classify_system_observe_objects
(ih_inferno_classify_system_t *system, ih_case_array_t *classified_objects);

#endif
