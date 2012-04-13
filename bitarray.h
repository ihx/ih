#ifndef ih_bitarray_h
#define ih_bitarray_h

#include "standard.h"

typedef uint64_t ih_bitarray_t;

#define IH_BITARRAY_SIZE 64

unsigned char ih_bitarray_get_uint8(ih_bitarray_t *bitarray,
    unsigned short position);
unsigned short ih_bitarray_get_uint16(ih_bitarray_t *bitarray,
    unsigned short position);
void ih_bitarray_randomize(ih_bitarray_t *bitarray);
void ih_bitarray_seed_center(ih_bitarray_t *bitarray);
void ih_bitarray_set_uint8(ih_bitarray_t *bitarray, unsigned short position,
    unsigned char value);
void ih_bitarray_set_uint16(ih_bitarray_t *bitarray, unsigned short position,
    unsigned short value);

#endif
