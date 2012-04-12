#include "bit.h"
#include "bitarray.h"
#include "wrap.h"

unsigned char ih_bitarray_get_uchar(ih_bitarray_t *bitarray,
    unsigned short position)
{
  unsigned short uchar = 0;
  unsigned short i;
  unsigned short place_value = 1;

  for (i = position; i < position + 8; i++) {
    uchar += place_value * ih_bit_get(*bitarray,
        ih_wrap(i, IH_BITARRAY_SIZE));
    place_value *= 2;
  }

  return uchar;
}

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

void ih_bitarray_set_uchar(ih_bitarray_t *bitarray, unsigned short position,
    unsigned char value)
{
  unsigned char place_value = 128;
  ih_bit_t bit;
  unsigned char remainder = value;
  short i;

  for (i = position + 7; i >= position; i--) {
    bit = remainder / place_value;
    remainder = remainder % place_value;
    ih_bit_set(bitarray, ih_wrap(i, IH_BITARRAY_SIZE), bit);
    place_value /= 2;
  }
}
