#ifndef ih_cxbitarray_h
#define ih_cxbitarray_h

#include "bit.h"
#include "bitarray.h"

struct ih_cxbitarray_t {
  ih_bit_t classification;
  ih_bitarray_t bitarray;
};
typedef struct ih_cxbitarray_t ih_cxbitarray_t;

#endif
