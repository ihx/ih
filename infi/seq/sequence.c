#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/infi/seq/point.h"
#include "ih/infi/seq/sequence.h"

struct ih_infi_seq_sequence_t {
  char *subject;
  ih_infi_seq_sequence_get_data_f get_data;
  ih_case_list_t *points;
};

ih_infi_seq_sequence_t *ih_infi_seq_sequence_create(char *subject,
    ih_infi_seq_sequence_get_data_f get_data)
{
  assert(subject);
  ih_infi_seq_sequence_t *sequence;
  ih_core_bool_t so_far_so_good;

  sequence = malloc(sizeof *sequence);
  if (sequence) {
    sequence->subject = strdup(subject);
    sequence->points = NULL;
    if (sequence->subject) {
      so_far_so_good = ih_core_bool_true;
    } else {
      so_far_so_good = ih_core_bool_false;
    }
  } else {
    ih_core_trace("malloc");
    so_far_so_good = ih_core_bool_false;
  }

  if (so_far_so_good) {
    sequence->points = ih_case_list_create(ih_infi_seq_point_compare,
        ih_infi_seq_point_copy, ih_infi_seq_point_destroy);
    if (!sequence->points) {
      so_far_so_good = ih_core_bool_false;
      ih_core_trace("ih_case_list_create");
    }
  }

  if (!so_far_so_good && sequence) {
    if (sequence->subject) {
      free(sequence->subject);
    }
    if (sequence->points) {
      ih_case_list_destroy(sequence->points);
    }
    free(sequence);
    sequence = NULL;
  }

  return sequence;
}

void ih_infi_seq_sequence_destroy(ih_infi_seq_sequence_t *sequence)
{
  assert(sequence);
  assert(sequence->subject);
  assert(sequence->points);

  free(sequence->subject);
  ih_case_list_destroy(sequence->points);
  free(sequence);
}

ih_core_bool_t ih_infi_seq_sequence_get_data(ih_infi_seq_sequence_t *sequence)
{
  return sequence->get_data(sequence);
}

ih_core_bool_t ih_infi_seq_sequence_get_data_from_nasdaq
(ih_infi_seq_sequence_t *sequence)
{
  return ih_core_bool_false;
}

ih_core_bool_t ih_infi_seq_sequence_get_data_from_random
(ih_infi_seq_sequence_t *sequence)
{
  assert(sequence);
  ih_infi_seq_point_t *point;
  unsigned long timestamp;
  char value[32];
  unsigned long i;
  double value_double;
  ih_core_bool_t success = ih_core_bool_true;

  ih_case_list_clear(sequence->points);
  for (i = 0; i < 256; i++) {
    timestamp = i;
    value_double = rand() / rand();
    sprintf(value, "%f", value_double);
    point = ih_infi_seq_point_create(timestamp, value);
    if (point) {
      if (!ih_case_list_add_last(sequence->points, point)) {
        ih_core_trace("ih_case_list_add_last");
        ih_infi_seq_point_destroy(point);
        success = ih_core_bool_false;
        break;
      }
    } else {
      ih_core_trace("ih_infi_seq_point_create");
      success = ih_core_bool_false;
      break;
    }
  }

  return success;
}

ih_core_bool_t ih_infi_seq_sequence_get_data_from_yahoo
(ih_infi_seq_sequence_t *sequence)
{
  return ih_core_bool_false;
}

ih_case_list_t *ih_infi_seq_sequence_get_points_last_n_copy
(ih_infi_seq_sequence_t *sequence, unsigned long n)
{
  assert(sequence);
  unsigned long points_size = ih_case_list_get_size(sequence->points);
  unsigned long start_point;
  unsigned long i;
  ih_case_list_t *points;
  ih_infi_seq_point_t *point;
  ih_infi_seq_point_t *point_copy;

  points = ih_case_list_create(ih_infi_seq_point_compare,
      ih_infi_seq_point_copy, ih_infi_seq_point_destroy);
  if (points) {
    if (points_size >= n) {
      start_point = points_size - n;
    } else {
      start_point = 0;
    }
    for (i = start_point; i < points_size; i++) {
      point = ih_case_list_find_at(sequence->points, i);
      assert(point);
      point_copy = ih_infi_seq_point_copy(point);
      if (point_copy) {
        if (!ih_case_list_add_last(points, point_copy)) {
          ih_core_trace("ih_case_list_add_last");
          ih_infi_seq_point_destroy(point_copy);
        }
      } else {
        ih_core_trace("ih_infi_seq_point_copy");
      }
    }
  } else {
    ih_core_trace("ih_case_list_create");
  }

  return points;
}

ih_case_list_t *ih_infi_seq_sequence_get_points_since_timestamp_copy
(ih_infi_seq_sequence_t *sequence, unsigned long timestamp)
{
  assert(sequence);
  unsigned long points_size = ih_case_list_get_size(sequence->points);
  unsigned long i;
  unsigned long start_point;
  ih_case_list_t *points;
  ih_infi_seq_point_t *point;
  ih_infi_seq_point_t *point_copy;

  points = ih_case_list_create(ih_infi_seq_point_compare,
      ih_infi_seq_point_copy, ih_infi_seq_point_destroy);
  if (points) {
    start_point = 0;
    ih_case_list_iterate_start(sequence->points);
    while ((point = ih_case_list_iterate_next(sequence->points))) {
      if (ih_infi_seq_point_get_timestamp(point) >= timestamp) {
        break;
      }
      start_point++;
    }
    for (i = start_point; i < points_size; i++) {
      point = ih_case_list_find_at(sequence->points, i);
      assert(point);
      point_copy = ih_infi_seq_point_copy(point);
      if (point_copy) {
        if (!ih_case_list_add_last(points, point_copy)) {
          ih_core_trace("ih_case_list_add_last");
          ih_infi_seq_point_destroy(point_copy);
        }
      } else {
        ih_core_trace("ih_infi_seq_point_copy");
      }
    }
  } else {
    ih_core_trace("ih_case_list_create");
  }

  return points;
}
