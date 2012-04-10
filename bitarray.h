#ifndef ih_bitarray_h
#define ih_bitarray_h

#include "standard.h"

typedef uint32_t ih_bitarray_t;

#define IH_BITARRAY_SIZE 32

void ih_bitarray_randomize(ih_bitarray_t *bitarray);

#endif
