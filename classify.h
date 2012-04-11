#ifndef ih_classify_h
#define ih_classify_h

#include "bit.h"
#include "bitarray.h"

enum ih_classify_style_t {
  ih_classify_style_majority,
  ih_classify_style_xor,
  ih_classify_style_zero_bit
};
typedef enum ih_classify_style_t ih_classify_style_t;

ih_bit_t ih_classify_crow(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...);

ih_bit_t ih_classify_eca(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...);

#define ih_classify ih_classify_eca

#endif
