#include "bit.h"
#include "bitarray.h"
#include "wrap.h"

unsigned char ih_bitarray_get_uint8(ih_bitarray_t *bitarray,
    unsigned short position)
{
  unsigned short uint8 = 0;
  unsigned short i;
  unsigned short place_value = 1;

  for (i = position; i < position + 8; i++) {
    uint8 += place_value * ih_bit_get(*bitarray,
        ih_wrap(i, IH_BITARRAY_SIZE));
    place_value *= 2;
  }

  return uint8;
}

unsigned short ih_bitarray_get_uint16(ih_bitarray_t *bitarray,
    unsigned short position)
{
  unsigned short uint16 = 0;
  unsigned short i;
  unsigned short place_value = 1;

  for (i = position; i < position + 16; i++) {
    uint16 += place_value * ih_bit_get(*bitarray,
        ih_wrap(i, IH_BITARRAY_SIZE));
    place_value *= 2;
  }

  return uint16;
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
  /*
    this {- 1} gets this compiling with bitarray == uint64_t
  */
  ih_bit_set(bitarray, (IH_BITARRAY_SIZE - 1) / 2, 1);
}
void ih_bitarray_set_uint8(ih_bitarray_t *bitarray, unsigned short position,
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

void ih_bitarray_set_uint16(ih_bitarray_t *bitarray, unsigned short position,
    unsigned short value)
{
  unsigned short place_value = 32768;
  ih_bit_t bit;
  unsigned short remainder = value;
  short i;

  for (i = position + 15; i >= position; i--) {
    bit = remainder / place_value;
    remainder = remainder % place_value;
    ih_bit_set(bitarray, ih_wrap(i, IH_BITARRAY_SIZE), bit);
    place_value /= 2;
  }
}
