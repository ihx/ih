#ifndef ih_bit_h
#define ih_bit_h

enum ih_bit_t {
  ih_bit_zero = 0,
  ih_bit_one = 1
};
typedef enum ih_bit_t ih_bit_t;

#define ih_bit_get(value, bit_index) ((value >> (bit_index)) & (uint64_t) 1)

#define ih_bit_set(value, bit_index, bit_value)              \
  if (bit_value) { *value |= ((uint64_t) 1 << (bit_index)); } \
  else { *value &= ~((uint64_t) 1 << (bit_index)); }

#endif
