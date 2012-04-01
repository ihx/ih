#include "ih/core/bitarray.h"
#include "ih/core/basic/long.h"
#include "ih/core/tools.h"

struct ih_core_bitarray_t {
  unsigned long array_size;
  ih_core_bit_t *array;
};

int ih_core_bitarray_compare(void *bitarray_a_object, void *bitarray_b_object)
{
  assert(bitarray_a_object);
  assert(bitarray_b_object);
  ih_core_bitarray_t *bitarray_a;
  ih_core_bitarray_t *bitarray_b;
  int compare_result;
  unsigned long each_bit;
  ih_core_bit_t bit_a;
  ih_core_bit_t bit_b;

  bitarray_a = bitarray_a_object;
  bitarray_b = bitarray_b_object;

  compare_result = ih_core_basic_long_compare(&bitarray_a->array_size,
      &bitarray_b->array_size);
  if (0 == compare_result) {
    for (each_bit = 0; each_bit < bitarray_a->array_size; each_bit++) {
      bit_a = *(bitarray_a->array + each_bit);
      bit_b = *(bitarray_b->array + each_bit);
      if (bit_a < bit_b) {
        compare_result = -1;
        break;
      } else if (bit_a > bit_b) {
        compare_result = 1;
        break;
      }
    }
  }

  return compare_result;
}

void *ih_core_bitarray_copy(void *bitarray_object)
{
  assert(bitarray_object);
  ih_core_bitarray_t *bitarray;
  ih_core_bitarray_t *bitarray_copy;
  unsigned long index;

  bitarray = bitarray_object;

  bitarray_copy = ih_core_bitarray_create(bitarray->array_size);
  if (bitarray_copy) {
    for (index = 0; index < bitarray->array_size; index++) {
      *(bitarray_copy->array + index) = *(bitarray->array + index);
    }
  } else {
    ih_core_trace("x_core_bitarray_create");
  }

  return bitarray_copy;
}

ih_core_bitarray_t *ih_core_bitarray_create(unsigned long size)
{
  assert(size > 0);
  ih_core_bitarray_t *bitarray;
  unsigned long array_memory_size;

  bitarray = malloc(sizeof *bitarray);
  if (bitarray) {
    array_memory_size = size * sizeof(ih_core_bit_t);
    bitarray->array = malloc(array_memory_size);
    if (bitarray->array) {
      memset(bitarray->array, '\0', array_memory_size);
      bitarray->array_size = size;
    } else {
      ih_core_trace("malloc");
      free(bitarray);
      bitarray = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return bitarray;
}

void ih_core_bitarray_destroy(void *bitarray_object)
{
  assert(bitarray_object);
  ih_core_bitarray_t *bitarray;

  bitarray = bitarray_object;

  free(bitarray->array);
  free(bitarray);

}

ih_core_bit_t ih_core_bitarray_get_bit_actual(ih_core_bitarray_t *bitarray,
    unsigned long index)
{
  return *(bitarray->array + index);
}

void ih_core_bitarray_set_all(ih_core_bitarray_t *bitarray)
{
  memset(bitarray->array, 1, bitarray->array_size * sizeof(ih_core_bit_t));
}

void ih_core_bitarray_set_bit_actual(ih_core_bitarray_t *bitarray,
    unsigned long index, ih_core_bit_t value)
{
  *(bitarray->array + index) = value;
}

unsigned long ih_core_bitarray_get_size(ih_core_bitarray_t *bitarray)
{
  return bitarray->array_size;
}

unsigned long ih_core_bitarray_get_memory_size_bytes
(ih_core_bitarray_t *bitarray)
{
  assert(bitarray);
  unsigned long size;

  size = sizeof *bitarray;
  size += bitarray->array_size * sizeof(ih_core_bit_t);

  return size;
}

void ih_core_bitarray_unset_all(ih_core_bitarray_t *bitarray)
{
  memset(bitarray->array, 0, bitarray->array_size * sizeof(ih_core_bit_t));
}
