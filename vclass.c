#include "bit.h"
#include "bitarray.h"
#include "classify.h"
#include "vclass.h"
#include "minigen.h"
#include "trace.h"

struct vclass_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
  ih_classify_style_t classify_style;
};
typedef struct vclass_context_t vclass_context_t;

double calculate_fitness(ih_genome_t genome, void *context)
{
  unsigned char rule_0 = ih_bitarray_get_uchar(&genome, 0);
  unsigned char rule_1 = ih_bitarray_get_uchar(&genome, 8);
  unsigned char rule_2 = ih_bitarray_get_uchar(&genome, 16);
  unsigned char rule_3 = ih_bitarray_get_uchar(&genome, 24);
  vclass_context_t *vclass_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < vclass_context->cxbitarrays_size; i++) {
    cxbitarray = vclass_context->cxbitarrays + i;
    classification = ih_classify(cxbitarray->bitarray,
        vclass_context->classify_style, 4, rule_0, rule_1, rule_2, rule_3);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / vclass_context->cxbitarrays_size;
}

void ih_vclass_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules)
{
  vclass_context_t context;
  ih_genome_t genome;

  context.cxbitarrays = cxbitarrays;
  context.cxbitarrays_size = cxbitarrays_size;
  context.classify_style = classify_style;

  genome = ih_minigen_evolve(calculate_fitness, required_fitness, &context);

  *(rules + 0) = ih_bitarray_get_uchar(&genome, 0);
  *(rules + 1) = ih_bitarray_get_uchar(&genome, 8);
  *(rules + 2) = ih_bitarray_get_uchar(&genome, 16);
  *(rules + 3) = ih_bitarray_get_uchar(&genome, 24);
}
