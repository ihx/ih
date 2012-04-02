#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/core/basic/unsigned_long.h"
#include "ih/infi/seq/point.h"

struct ih_infi_seq_point_t {
  unsigned long timestamp;
  char *value;
};

int ih_infi_seq_point_compare(void *point_a_object, void *point_b_object)
{
  assert(point_a_object);
  assert(point_b_object);
  ih_infi_seq_point_t *point_a = point_a_object;
  ih_infi_seq_point_t *point_b = point_b_object;

  return ih_core_basic_unsigned_long_compare(&point_a->timestamp,
      &point_b->timestamp);
}

void *ih_infi_seq_point_copy(void *point_object)
{
  assert(point_object);
  ih_infi_seq_point_t *point = point_object;
  return ih_infi_seq_point_create(point->timestamp, point->value);
}

ih_infi_seq_point_t *ih_infi_seq_point_create(unsigned long timestamp,
    char *value)
{
  assert(value);
  ih_infi_seq_point_t *point;

  point = malloc(sizeof *point);
  if (point) {
    point->timestamp = timestamp;
    point->value = strdup(value);
    if (!point->value) {
      ih_core_trace("strdup");
      free(point);
      point = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return point;
}

void ih_infi_seq_point_destroy(void *point_object)
{
  assert(point_object);
  ih_infi_seq_point_t *point = point_object;
  assert(point->value);

  free(point->value);
  free(point);
}

unsigned long ih_infi_seq_point_get_timestamp(ih_infi_seq_point_t *point)
{
  return point->timestamp;
}

char *ih_infi_seq_point_get_value(ih_infi_seq_point_t *point)
{
  return point->value;
}