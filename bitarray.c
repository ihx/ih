#include "bit.h"
#include "bitarray.h"

void ih_bitarray_randomize(ih_bitarray_t *bitarray)
{
  unsigned char i;

  for (i = 0; i < IH_BITARRAY_SIZE; i++) {
    ih_bit_set(bitarray, i, random() % 2);
  }
}
