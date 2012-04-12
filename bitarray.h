#ifndef ih_bitarray_h
#define ih_bitarray_h

#include "standard.h"

typedef uint32_t ih_bitarray_t;

#define IH_BITARRAY_SIZE 32

unsigned char ih_bitarray_get_uchar(ih_bitarray_t *bitarray,
    unsigned short position);
void ih_bitarray_randomize(ih_bitarray_t *bitarray);
void ih_bitarray_seed_center(ih_bitarray_t *bitarray);
void ih_bitarray_set_uchar(ih_bitarray_t *bitarray, unsigned short position,
    unsigned char value);

#endif
