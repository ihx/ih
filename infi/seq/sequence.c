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

ih_core_bool_t ih_infi_seq_sequence_get_data_from_yahoo(ih_infi_seq_sequence_t *sequence)
{
  return ih_core_bool_false;
}

ih_case_list_t *ih_infi_seq_sequence_get_points_last_n
(ih_infi_seq_sequence_t *sequence, unsigned long n)
{
  return NULL;
}

ih_case_list_t *ih_infi_seq_sequence_get_points_since_timestamp
(ih_infi_seq_sequence_t *sequence, unsigned long timestamp)
{
  return NULL;
}

/*
char *ih_infi_seq_sequence_get_subject(ih_infi_seq_sequence_t *sequence)
{
  return sequence->subject;
}
*/
