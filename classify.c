#include "ca.h"
#include "classify.h"
#include "wrap.h"

#define TIME_STEPS IH_BITARRAY_SIZE

ih_bit_t ih_classify_eca(ih_bitarray_t bitarray, unsigned long rule,
    ih_classify_style_t style)
{
  ih_bitarray_t history[TIME_STEPS];
  unsigned char i;
  unsigned char j;
  ih_bit_t cell_value;
  unsigned short neighborhood;
  ih_bit_t a;
  ih_bit_t b;
  ih_bit_t c;
  ih_bit_t classification;
  unsigned short total_zero;
  unsigned short total_one;

  for (j = 0; j < IH_BITARRAY_SIZE; j++) {
    ih_bit_set(&history[0], j, ih_bit_get(bitarray, j));
  }

  for (i = 1; i < TIME_STEPS; i++) {
    for (j = 0; j < IH_BITARRAY_SIZE; j++) {
      a = ih_bit_get(history[i - 1], ih_wrap(j - 1, IH_BITARRAY_SIZE));
      b = ih_bit_get(history[i - 1], ih_wrap(j, IH_BITARRAY_SIZE));
      c = ih_bit_get(history[i - 1], ih_wrap(j + 1, IH_BITARRAY_SIZE));
      neighborhood = (4 * a) + (2 * b) + c;
      cell_value = ih_ca_calculate(rule, neighborhood);
      ih_bit_set(&history[i], j, cell_value);
    }
  }

  switch (style) {
    case ih_classify_style_xor:
      classification = ih_bit_get(history[TIME_STEPS - 1], 0);
      for (j = 1; j < IH_BITARRAY_SIZE; j++) {
        classification ^= ih_bit_get(history[TIME_STEPS - 1], j);
      }
      break;
    case ih_classify_style_zero_bit:
      classification = ih_bit_get(history[TIME_STEPS - 1], 0);
      break;
    case ih_classify_style_majority:
    default:
      total_zero = 0;
      total_one = 0;
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        if (ih_bit_get(history[TIME_STEPS - 1], j)) {
          total_one++;
        } else {
          total_zero++;
        }
      }
      if (total_one > total_zero) {
        classification = ih_bit_one;
      } else {
        classification = ih_bit_zero;
      }
      break;
  }

  return classification;
}
