#ifndef ih_inferno_computer_output_h
#define ih_inferno_computer_output_h

#include "ih/core/bit.h"

#define IH_INFERNO_COMPUTER_OUTPUT_BITS 32

struct ih_inferno_computer_output_t {
  ih_core_bit_t bits[IH_INFERNO_COMPUTER_OUTPUT_BITS];
};
typedef struct ih_inferno_computer_output_t ih_inferno_computer_output_t;

void ih_inferno_computer_output_free(ih_inferno_computer_output_t *output);

void ih_inferno_computer_output_init(ih_inferno_computer_output_t *output);

#endif
