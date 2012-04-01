#include "ih/core/standard.h"
#include "ih/inferno/computer/output.h"

void ih_inferno_computer_output_free(ih_inferno_computer_output_t *output) {}

void ih_inferno_computer_output_init(ih_inferno_computer_output_t *output)
{
  memset(output->bits, 0, IH_INFERNO_COMPUTER_OUTPUT_BITS);
}
