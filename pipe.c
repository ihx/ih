#include "bit.h"
#include "bitarray.h"
#include "ca.h"
#include "classify.h"
#include "minigen.h"
#include "trace.h"
#include "pipe.h"
#include "wrap.h"

#define TIME_STEPS IH_BITARRAY_SIZE
#undef DEBUG_PRINT

struct pipe_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
  ih_classify_style_t classify_style;
};
typedef struct pipe_context_t pipe_context_t;

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
  pipe_context_t *pipe_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < pipe_context->cxbitarrays_size; i++) {
    cxbitarray = pipe_context->cxbitarrays + i;
    classification = ih_pipe_classify(cxbitarray->bitarray,
        pipe_context->classify_style, 8, rule_0, rule_1, rule_2, rule_3,
        rule_4, rule_5, rule_6, rule_7);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / pipe_context->cxbitarrays_size;
}

ih_bit_t ih_pipe_classify(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...)
{
  ih_bitarray_t history[TIME_STEPS];
  unsigned char i;
  unsigned char j;
  ih_bit_t cell_value;
  unsigned short neighborhood;
  ih_bit_t a;
  ih_bit_t b;
  ih_bit_t c;
  ih_bit_t classification;
  unsigned short total_zero;
  unsigned short total_one;
  va_list ap;
  unsigned long rule;
  unsigned short r;

  va_start(ap, rule_count);
  for (r = 0; r < rule_count; r++) {
    rule = va_arg(ap, unsigned long);
    if (0 == r) {
      history[0] = bitarray;
    } else {
      history[0] = history[TIME_STEPS - 1];
    }
#ifdef DEBUG_PRINT
    for (j = 0; j < IH_BITARRAY_SIZE; j++) {
      printf("%d", ih_bit_get(history[0], j));
    }
    printf("\n");
#endif

    for (i = 1; i < TIME_STEPS; i++) {
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        a = ih_bit_get(history[i - 1], ih_wrap(j - 1, IH_BITARRAY_SIZE));
        b = ih_bit_get(history[i - 1], ih_wrap(j, IH_BITARRAY_SIZE));
        c = ih_bit_get(history[i - 1], ih_wrap(j + 1, IH_BITARRAY_SIZE));
        neighborhood = (4 * a) + (2 * b) + c;
        cell_value = ih_ca_calculate(rule, neighborhood);
        ih_bit_set(&history[i], j, cell_value);
#ifdef DEBUG_PRINT
        printf("%d", cell_value);
#endif
      }
#ifdef DEBUG_PRINT
      printf("\n");
#endif
    }
  }
  va_end(ap);

  switch (style) {
    case ih_classify_style_xor:
      classification = ih_bit_get(history[TIME_STEPS - 1], 0);
      for (j = 1; j < IH_BITARRAY_SIZE; j++) {
        classification ^= ih_bit_get(history[TIME_STEPS - 1], j);
      }
      break;
    case ih_classify_style_zero_bit:
      classification = ih_bit_get(history[TIME_STEPS - 1], 0);
      break;
    case ih_classify_style_majority:
    default:
      total_zero = 0;
      total_one = 0;
      for (j = 0; j < IH_BITARRAY_SIZE; j++) {
        if (ih_bit_get(history[TIME_STEPS - 1], j)) {
          total_one++;
        } else {
          total_zero++;
        }
      }
      if (total_one > total_zero) {
        classification = ih_bit_one;
      } else {
        classification = ih_bit_zero;
      }
      break;
  }

  return classification;
}

void ih_pipe_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned char *rules)
{
  pipe_context_t context;
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
