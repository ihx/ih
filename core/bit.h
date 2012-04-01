#ifndef ih_core_bit_h
#define ih_core_bit_h

#include "ih/core/object.h"

enum ih_core_bit_t {
  ih_core_bit_zero = 0,
  ih_core_bit_one = 1,
};
typedef enum ih_core_bit_t ih_core_bit_t;

int ih_core_bit_compare(void *bit_a_object, void *bit_b_object);

void *ih_core_bit_copy(void *bit_object);

void ih_core_bit_destroy(void *bit_object);

#endif
