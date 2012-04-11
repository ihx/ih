#include "bit.h"
#include "bitarray.h"
#include "classify.h"
#include "evoclass.h"
#include "minigen.h"
#include "trace.h"

struct evoclass_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
};
typedef struct evoclass_context_t evoclass_context_t;

double calculate_fitness(ih_genome_t genome, void *context)
{
  unsigned char rule_0 = ih_bitarray_get_uchar(&genome, 0);
  unsigned char rule_1 = ih_bitarray_get_uchar(&genome, 8);
  unsigned char rule_2 = ih_bitarray_get_uchar(&genome, 16);
  unsigned char rule_3 = ih_bitarray_get_uchar(&genome, 24);
  evoclass_context_t *evoclass_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < evoclass_context->cxbitarrays_size; i++) {
    cxbitarray = evoclass_context->cxbitarrays + i;
    classification = ih_classify(cxbitarray->bitarray,
        ih_classify_style_majority, 4, rule_0, rule_1, rule_2, rule_3);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / evoclass_context->cxbitarrays_size;
}

void ih_evoclass_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, unsigned long *rules)
{
  evoclass_context_t context;
  ih_minigen_t *minigen;
  ih_genome_t genome;

  context.cxbitarrays = cxbitarrays;
  context.cxbitarrays_size = cxbitarrays_size;

  minigen = ih_minigen_create(calculate_fitness, 0.9, &context);
  genome = ih_minigen_generate(minigen);
  ih_minigen_destroy(minigen);

  *(rules + 0) = ih_bitarray_get_uchar(&genome, 0);
  *(rules + 1) = ih_bitarray_get_uchar(&genome, 8);
  *(rules + 2) = ih_bitarray_get_uchar(&genome, 16);
  *(rules + 3) = ih_bitarray_get_uchar(&genome, 24);
}
