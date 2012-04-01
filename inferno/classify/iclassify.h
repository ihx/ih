#ifndef ih_inferno_classify_iclassify_h
#define ih_inferno_classify_iclassify_h

#include "ih/core/log.h"
#include "ih/case/array.h"
#include "ih/core/bitarray.h"

typedef void *(*ih_inferno_classify_iclassify_create_f)
  (ih_case_array_t *classified_objects, ih_core_log_t *log);

typedef void (*ih_inferno_classify_iclassify_destroy_f)(void *system_void);

typedef ih_core_bit_t (*ih_inferno_classify_iclassify_classify_object_f)
(void *system_void, ih_core_bitarray_t *object);

typedef ih_core_bool_t (*ih_inferno_classify_iclassify_learn_f)(void *system_void);

typedef ih_core_bool_t (*ih_inferno_classify_iclassify_observe_object_f)
(void *system_void, ih_core_bitarray_t *classified_object);

struct ih_inferno_classify_iclassify_t {
  ih_inferno_classify_iclassify_create_f create;
  ih_inferno_classify_iclassify_destroy_f destroy;
  ih_inferno_classify_iclassify_classify_object_f classify_object;
  ih_inferno_classify_iclassify_learn_f learn;
  ih_inferno_classify_iclassify_observe_object_f observe_object;
};
typedef struct ih_inferno_classify_iclassify_t ih_inferno_classify_iclassify_t;

void ih_inferno_classify_iclassify_free(ih_inferno_classify_iclassify_t *iclassify);

void ih_inferno_classify_iclassify_init(ih_inferno_classify_iclassify_t *iclassify,
    ih_inferno_classify_iclassify_create_f create,
    ih_inferno_classify_iclassify_destroy_f destroy,
    ih_inferno_classify_iclassify_classify_object_f classify_object,
    ih_inferno_classify_iclassify_learn_f learn,
    ih_inferno_classify_iclassify_observe_object_f observe_object);

#endif
