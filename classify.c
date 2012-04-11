#include "ca.h"
#include "classify.h"
#include "wrap.h"

#define TIME_STEPS IH_BITARRAY_SIZE
#undef DEBUG_PRINT

ih_bit_t ih_classify_crow(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...)
{
  ih_bitarray_t history[TIME_STEPS];
  unsigned char i;
  unsigned char j;
  ih_bit_t cell_value;
  unsigned short neighborhood;
  ih_bit_t a;
  ih_bit_t b;
  ih_bit_t c;
  ih_bit_t d;
  ih_bit_t classification;
  unsigned short total_zero;
  unsigned short total_one;
  va_list ap;
  unsigned long rule;
  unsigned short r;

  va_start(ap, rule_count);
  for (r = 0; r < rule_count; r++) {
    rule = va_arg(ap, unsigned long);
    if (0 == r) {
      history[0] = bitarray;
      history[1] = bitarray;
    } else {
      history[0] = history[TIME_STEPS - 2];
      history[1] = history[TIME_STEPS - 1];
    }
#ifdef DEBUG_PRINT
    for (i = 0; i < 2; i++) {
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        printf("%d", ih_bit_get(history[i], j));
      }
    }
    printf("\n");
#endif

    for (i = 2; i < TIME_STEPS; i++) {
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        a = ih_bit_get(history[i - 1], ih_wrap(j - 1, IH_BITARRAY_SIZE));
        b = ih_bit_get(history[i - 1], ih_wrap(j, IH_BITARRAY_SIZE));
        c = ih_bit_get(history[i - 1], ih_wrap(j + 1, IH_BITARRAY_SIZE));
        d = ih_bit_get(history[i - 2], ih_wrap(j, IH_BITARRAY_SIZE));
        neighborhood = (8 * a) + (4 * b) + (2 * c) + d;
        cell_value = ih_ca_calculate(rule, neighborhood);
        ih_bit_set(&history[i], j, cell_value);
#ifdef DEBUG_PRINT
        printf("%d", cell_value);
#endif
      }
#ifdef DEBUG_PRINT
      printf("\n");
#endif
    }
  }
  va_end(ap);

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

ih_bit_t ih_classify_eca(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...)
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
  va_list ap;
  unsigned long rule;
  unsigned short r;

  va_start(ap, rule_count);
  for (r = 0; r < rule_count; r++) {
    rule = va_arg(ap, unsigned long);
    if (0 == r) {
      history[0] = bitarray;
    } else {
      history[0] = history[TIME_STEPS - 1];
    }
#ifdef DEBUG_PRINT
    for (j = 0; j < IH_BITARRAY_SIZE; j++) {
      printf("%d", ih_bit_get(history[0], j));
    }
    printf("\n");
#endif

    for (i = 1; i < TIME_STEPS; i++) {
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        a = ih_bit_get(history[i - 1], ih_wrap(j - 1, IH_BITARRAY_SIZE));
        b = ih_bit_get(history[i - 1], ih_wrap(j, IH_BITARRAY_SIZE));
        c = ih_bit_get(history[i - 1], ih_wrap(j + 1, IH_BITARRAY_SIZE));
        neighborhood = (4 * a) + (2 * b) + c;
        cell_value = ih_ca_calculate(rule, neighborhood);
        ih_bit_set(&history[i], j, cell_value);
#ifdef DEBUG_PRINT
        printf("%d", cell_value);
#endif
      }
#ifdef DEBUG_PRINT
      printf("\n");
#endif
    }
  }
  va_end(ap);

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
