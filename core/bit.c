#include "ih/core/bit.h"
#include "ih/core/tools.h"

int ih_core_bit_compare(void *bit_a_object, void *bit_b_object)
{
  ih_core_bit_t *bit_a;
  ih_core_bit_t *bit_b;
  int compare;

  bit_a = bit_a_object;
  bit_b = bit_b_object;
  if (*bit_a > *bit_b) {
    compare = 1;
  } else if (*bit_a < *bit_b) {
    compare = -1;
  } else {
    compare = 0;
  }

  return compare;
}

void *ih_core_bit_copy(void *bit_object)
{
  assert(bit_object);
  ih_core_bit_t *bit;
  ih_core_bit_t *bit_copy;

  bit = bit_object;
  bit_copy = malloc(sizeof *bit_copy);
  if (bit_copy) {
    *bit_copy = *bit;
  } else {
    ih_core_trace("mallloc");
  }

  return bit_copy;
}

void ih_core_bit_destroy(void *bit_object)
{
  assert(bit_object);
  free(bit_object);
}
