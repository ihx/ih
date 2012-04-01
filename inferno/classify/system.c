#include "ih/inferno/archetype/system.h"
#include "ih/inferno/classify/iclassify.h"
#include "ih/inferno/classify/system.h"
#include "ih/core/standard.h"

struct ih_inferno_classify_system_t {
  ih_inferno_classify_iclassify_t iclassify;
  void *classify_object;
  ih_core_log_t *log;
};

static void init_iclassify(ih_inferno_classify_iclassify_t *iclassify,
    ih_inferno_classify_algorithm_t algorithm);

ih_inferno_classify_system_t *ih_inferno_classify_system_create
(ih_case_array_t *classified_objects,
    ih_inferno_classify_algorithm_t algorithm, ih_core_log_t *log)
{
  assert(classified_objects);
  assert(ih_case_array_get_size(classified_objects) > 0);
  assert(ih_core_bitarray_get_size(ih_case_array_find
          (classified_objects, 0)) >= 2);
  assert(log);
  ih_inferno_classify_system_t *system;

  system = malloc(sizeof *system);
  if (system) {
    system->log = log;
    init_iclassify(&system->iclassify, algorithm);
    system->classify_object = system->iclassify.create(classified_objects,
        log);
    if (!system->classify_object) {
      ih_core_log_trace(log, "clss", "create");
      free(system);
      system = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_inferno_classify_system_destroy(ih_inferno_classify_system_t *system)
{
  assert(system);

  system->iclassify.destroy(system->classify_object);
  free(system);
}

ih_core_bit_t ih_inferno_classify_system_classify_object
(ih_inferno_classify_system_t *system, ih_core_bitarray_t *object)
{
  return system->iclassify.classify_object(system->classify_object, object);
}

ih_case_array_t *ih_inferno_classify_system_classify_objects
(ih_inferno_classify_system_t *system, ih_case_array_t *objects)
{
  assert(system);
  assert(objects);
  ih_core_bitarray_t *object;
  ih_case_array_t *classes;
  unsigned long object_count;
  /*  ih_core_bit_t class;  */
  ih_core_bit_t *class_object;
  unsigned long index;

  object_count = ih_case_array_get_size(objects);
  classes = ih_case_array_create(object_count, ih_core_bit_compare,
      ih_core_bit_copy, ih_core_bit_destroy);
  if (classes) {
    ih_case_array_iterate_start(objects);
    index = 0;
    while ((object = ih_case_array_iterate_next(objects))) {
      /*
      class
        = system->iclassify.classify_object(system->classify_object, object);
      */
      class_object = malloc(sizeof *class_object);
      if (class_object) {
        ih_case_array_add(classes, index, class_object);
      } else {
        ih_core_log_trace(system->log, "clss", "malloc");
      }
      index++;
    }
  } else {
    ih_core_trace("x_case_array_create");
  }

  return classes;
}

ih_core_bool_t ih_inferno_classify_system_learn
(ih_inferno_classify_system_t *system,
    unsigned long max_wall_time_microseconds)
{
  assert(system);
  struct timeval start_time;
  ih_core_bool_t success;

  gettimeofday(&start_time, NULL);

  success = ih_core_bool_true;
  do {
    if (!system->iclassify.learn(system->classify_object)) {
      success = ih_core_bool_false;
      ih_core_log_trace(system->log, "clss", "learn");
    }
  } while (ih_core_time_is_remaining_microseconds
      (&start_time, max_wall_time_microseconds));

  return success;
}

ih_core_bool_t ih_inferno_classify_system_observe_object
(ih_inferno_classify_system_t *system, ih_core_bitarray_t *classified_object)
{
  return system->iclassify.observe_object(system->classify_object,
      classified_object);
}

ih_core_bool_t ih_inferno_classify_system_observe_objects
(ih_inferno_classify_system_t *system, ih_case_array_t *classified_objects)
{
  assert(system);
  assert(classified_objects);
  ih_core_bool_t success;
  ih_core_bitarray_t *object;

  success = ih_core_bool_true;

  ih_case_array_iterate_start(classified_objects);
  while ((object = ih_case_array_iterate_next(classified_objects))) {
    if (!system->iclassify.observe_object(system->classify_object, object)) {
      success = ih_core_bool_false;
      ih_core_log_trace(system->log, "clss", "observe_object");
    }
  }

  return success;
}

void init_iclassify(ih_inferno_classify_iclassify_t *iclassify,
    ih_inferno_classify_algorithm_t algorithm)
{
  assert(iclassify);

  switch (algorithm) {
    default:
    case IH_INFERNO_CLASSIFY_ALGORITHM_ARCHETYPE:
      ih_inferno_archetype_system_init_iclassify(iclassify);
      break;
  }
}
