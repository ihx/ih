#include "bit.h"
#include "bitarray.h"
#include "classify.h"
#include "minigen.h"
#include "trace.h"
#include "tunnel.h"

struct tunnel_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
  ih_classify_style_t classify_style;
};
typedef struct tunnel_context_t tunnel_context_t;

static double calculate_fitness(ih_genome_t genome, void *context);

double calculate_fitness(ih_genome_t genome, void *context)
{
  unsigned char rule_0 = ih_bitarray_get_uint8(&genome, 0);
  unsigned char rule_1 = ih_bitarray_get_uint8(&genome, 8);
  unsigned char rule_2 = ih_bitarray_get_uint8(&genome, 16);
  unsigned char rule_3 = ih_bitarray_get_uint8(&genome, 24);
  unsigned char rule_4 = ih_bitarray_get_uint8(&genome, 32);
  unsigned char rule_5 = ih_bitarray_get_uint8(&genome, 40);
  unsigned char rule_6 = ih_bitarray_get_uint8(&genome, 48);
  unsigned char rule_7 = ih_bitarray_get_uint8(&genome, 56);
  tunnel_context_t *tunnel_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < tunnel_context->cxbitarrays_size; i++) {
    cxbitarray = tunnel_context->cxbitarrays + i;
    classification = ih_classify(cxbitarray->bitarray,
        tunnel_context->classify_style, 8, rule_0, rule_1, rule_2, rule_3,
        rule_4, rule_5, rule_6, rule_7);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / tunnel_context->cxbitarrays_size;
}

void ih_tunnel_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules)
{
  tunnel_context_t context;
  ih_genome_t genome;

  context.cxbitarrays = cxbitarrays;
  context.cxbitarrays_size = cxbitarrays_size;
  context.classify_style = classify_style;

  genome = ih_minigen_evolve(calculate_fitness, required_fitness, &context);

  *(rules + 0) = ih_bitarray_get_uint8(&genome, 0);
  *(rules + 1) = ih_bitarray_get_uint8(&genome, 8);
  *(rules + 2) = ih_bitarray_get_uint8(&genome, 16);
  *(rules + 3) = ih_bitarray_get_uint8(&genome, 24);
  *(rules + 4) = ih_bitarray_get_uint8(&genome, 32);
  *(rules + 5) = ih_bitarray_get_uint8(&genome, 40);
  *(rules + 6) = ih_bitarray_get_uint8(&genome, 48);
  *(rules + 7) = ih_bitarray_get_uint8(&genome, 56);
}
