#include "bit.h"
#include "bitarray.h"
#include "classify.h"
#include "genetic.h"
#include "minigen.h"
#include "trace.h"
#include "tube.h"

struct tube_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
  ih_classify_style_t classify_style;
};
typedef struct tube_context_t tube_context_t;

static double calculate_fitness(ih_genome_t genome, void *context);

double calculate_fitness(ih_genome_t genome, void *context)
{
  unsigned short rule_0 = ih_bitarray_get_uint16(&genome, 0);
  unsigned short rule_1 = ih_bitarray_get_uint16(&genome, 16);
  unsigned short rule_2 = ih_bitarray_get_uint16(&genome, 32);
  unsigned short rule_3 = ih_bitarray_get_uint16(&genome, 48);
  tube_context_t *tube_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < tube_context->cxbitarrays_size; i++) {
    cxbitarray = tube_context->cxbitarrays + i;
    classification = ih_classify_crow(cxbitarray->bitarray,
        tube_context->classify_style, 8, rule_0, rule_1, rule_2, rule_3);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / tube_context->cxbitarrays_size;
}

void ih_tube_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules)
{
  tube_context_t context;
  ih_genome_t genome;
  ih_genetic_t *genetic;
  double fitness;

  context.cxbitarrays = cxbitarrays;
  context.cxbitarrays_size = cxbitarrays_size;
  context.classify_style = classify_style;

  /*
  genome = ih_minigen_evolve(calculate_fitness, required_fitness, &context);
  */
  genetic = ih_genetic_create(calculate_fitness, &context, NULL);
  ih_genetic_evolve(genetic, required_fitness, &genome, &fitness);
  ih_genetic_destroy(genetic);

  *(rules + 0) = ih_bitarray_get_uint16(&genome, 0);
  *(rules + 1) = ih_bitarray_get_uint16(&genome, 16);
  *(rules + 2) = ih_bitarray_get_uint16(&genome, 32);
  *(rules + 3) = ih_bitarray_get_uint16(&genome, 48);
}
