#include "bit.h"
#include "bitarray.h"

void ih_bitarray_randomize(ih_bitarray_t *bitarray)
{
  unsigned char i;

  for (i = 0; i < IH_BITARRAY_SIZE; i++) {
    ih_bit_set(bitarray, i, random() % 2);
  }
}

void ih_bitarray_seed_center(ih_bitarray_t *bitarray)
{
  *bitarray = 0;
  ih_bit_set(bitarray, IH_BITARRAY_SIZE / 2, 1);
}
