#include "ca.h"
#include "bit.h"
#include "sieve.h"
#include "genetic.h"
#include "genome.h"
#include "minigen.h"
#include "wrap.h"

#define TIME_STEPS 16

struct sieve_context_t {
  ih_cxbitarray_t *cxbitarrays;
  unsigned long cxbitarrays_size;
  ih_classify_style_t classify_style;
};
typedef struct sieve_context_t sieve_context_t;

static void calculate_ca(ih_bitarray_t ca[], unsigned char rule);
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
  sieve_context_t *sieve_context = context;
  unsigned i;
  ih_bit_t classification;
  ih_cxbitarray_t *cxbitarray;
  unsigned long total_correct = 0;

  for (i = 0; i < sieve_context->cxbitarrays_size; i++) {
    cxbitarray = sieve_context->cxbitarrays + i;
    classification = ih_sieve_classify(cxbitarray->bitarray,
        sieve_context->classify_style, rule_0, rule_1, rule_2, rule_3,
        rule_4, rule_5, rule_6, rule_7);
    if (classification == cxbitarray->classification) {
      total_correct++;
    }
  }

  return (double) total_correct / sieve_context->cxbitarrays_size;
}

void calculate_ca(ih_bitarray_t ca[], unsigned char rule)
{
  unsigned char i;
  unsigned char j;
  ih_bit_t a;
  ih_bit_t b;
  ih_bit_t c;
  unsigned char neighborhood;
  ih_bit_t cell_value;

  for (i = 1; i < TIME_STEPS; i++) {
    for (j = 0; j < 16; j++) {
      a = ih_bit_get(ca[i - 1], ih_wrap(j - 1, 16));
      b = ih_bit_get(ca[i - 1], ih_wrap(j, 16));
      c = ih_bit_get(ca[i - 1], ih_wrap(j + 1, 16));
      neighborhood = (4 * a) + (2 * b) + c;
      cell_value = ih_ca_calculate(rule, neighborhood);
      ih_bit_set(&ca[i], j, cell_value);
    }
  }
}

ih_bit_t ih_sieve_classify(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned char rule_0, unsigned char rule_1, unsigned char rule_2,
    unsigned char rule_3, unsigned char rule_4, unsigned char rule_5,
    unsigned char rule_6, unsigned char rule_7)
{
  ih_bitarray_t ca_0[TIME_STEPS];
  ih_bitarray_t ca_1[TIME_STEPS];
  ih_bitarray_t ca_2[TIME_STEPS];
  ih_bitarray_t ca_3[TIME_STEPS];
  ih_bitarray_t ca_4[TIME_STEPS];
  ih_bitarray_t ca_5[TIME_STEPS];
  ih_bitarray_t ca_6[TIME_STEPS];
  ih_bitarray_t ca_7[TIME_STEPS];
  unsigned char i;
  ih_bit_t classification;
  unsigned char total_one;
  unsigned char total_zero;

  for (i = 0; i < 16; i++) {
    ih_bit_set(&ca_0[0], i, ih_bit_get(bitarray, i));
  }
  for (i = 0; i < 16; i++) {
    ih_bit_set(&ca_1[0], i, ih_bit_get(bitarray, i + 16));
  }
  for (i = 0; i < 16; i++) {
    ih_bit_set(&ca_2[0], i, ih_bit_get(bitarray, i + 32));
  }
  for (i = 0; i < 16; i++) {
    ih_bit_set(&ca_3[0], i, ih_bit_get(bitarray, i + 48));
  }

  calculate_ca(ca_0, rule_0);
  calculate_ca(ca_1, rule_1);
  calculate_ca(ca_2, rule_2);
  calculate_ca(ca_3, rule_3);

  for (i = 0; i < 16; i++) {
    if (0 == (i % 2)) {
      ih_bit_set(&ca_4[0], i, ih_bit_get(ca_0[TIME_STEPS - 1], i));
      ih_bit_set(&ca_5[0], i, ih_bit_get(ca_2[TIME_STEPS - 1], i));
    } else {
      ih_bit_set(&ca_4[0], i, ih_bit_get(ca_1[TIME_STEPS - 1], i));
      ih_bit_set(&ca_5[0], i, ih_bit_get(ca_3[TIME_STEPS - 1], i));
    }
  }
  /*
  for (i = 0; i < 8; i++) {
    ih_bit_set(&ca_4[0], i, ih_bit_get(ca_0[TIME_STEPS - 1], i));
    ih_bit_set(&ca_5[0], i, ih_bit_get(ca_2[TIME_STEPS - 1], i));
  }
  for (i = 8; i < 16; i++) {
    ih_bit_set(&ca_4[0], i, ih_bit_get(ca_1[TIME_STEPS - 1], i));
    ih_bit_set(&ca_5[0], i, ih_bit_get(ca_3[TIME_STEPS - 1], i));
  }
  */

  calculate_ca(ca_4, rule_4);
  calculate_ca(ca_5, rule_5);

  for (i = 0; i < 16; i++) {
    if (0 == (i % 2)) {
      ih_bit_set(&ca_6[0], i, ih_bit_get(ca_4[TIME_STEPS - 1], i));
    } else {
      ih_bit_set(&ca_6[0], i, ih_bit_get(ca_5[TIME_STEPS - 1], i));
    }
  }
  /*
  for (i = 0; i < 8; i++) {
    ih_bit_set(&ca_6[0], i, ih_bit_get(ca_4[TIME_STEPS - 1], i));
  }
  for (i = 8; i < 16; i++) {
    ih_bit_set(&ca_6[0], i, ih_bit_get(ca_5[TIME_STEPS - 1], i));
  }
  */

  calculate_ca(ca_6, rule_6);

  for (i = 0; i < 16; i++) {
    ih_bit_set(&ca_7[0], i, ih_bit_get(ca_6[TIME_STEPS - 1], i));
  }

  calculate_ca(ca_7, rule_7);

  switch (style) {
    case ih_classify_style_xor:
      classification = ih_bit_get(ca_7[TIME_STEPS - 1], 0);
      for (i = 1; i < 16; i++) {
        classification ^= ih_bit_get(ca_7[TIME_STEPS - 1], i);
      }
      break;
    case ih_classify_style_zero_bit:
      classification = ih_bit_get(ca_7[TIME_STEPS - 1], 0);
      break;
    case ih_classify_style_majority:
    default:
      total_zero = 0;
      total_one = 0;
      for (i = 0; i < 16; i++) {
        if (ih_bit_get(ca_7[TIME_STEPS - 1], i)) {
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

void ih_sieve_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned char *rules)
{
  sieve_context_t context;
  ih_genome_t genome;
  ih_genetic_t *genetic;
  double fitness;

  context.cxbitarrays = cxbitarrays;
  context.cxbitarrays_size = cxbitarrays_size;
  context.classify_style = classify_style;

  genetic = ih_genetic_create(calculate_fitness, &context, NULL);
  if (genetic) {
    /*
    genome = ih_minigen_evolve(calculate_fitness, required_fitness, &context);
    */
    ih_genetic_evolve(genetic, required_fitness, &genome, &fitness);
    ih_genetic_destroy(genetic);

    *(rules + 0) = ih_bitarray_get_uint8(&genome, 0);
    *(rules + 1) = ih_bitarray_get_uint8(&genome, 8);
    *(rules + 2) = ih_bitarray_get_uint8(&genome, 16);
    *(rules + 3) = ih_bitarray_get_uint8(&genome, 24);
    *(rules + 4) = ih_bitarray_get_uint8(&genome, 32);
    *(rules + 5) = ih_bitarray_get_uint8(&genome, 40);
    *(rules + 6) = ih_bitarray_get_uint8(&genome, 48);
    *(rules + 7) = ih_bitarray_get_uint8(&genome, 56);
  } else {
    *(rules + 0) = 0;
    *(rules + 1) = 0;
    *(rules + 2) = 0;
    *(rules + 3) = 0;
    *(rules + 4) = 0;
    *(rules + 5) = 0;
    *(rules + 6) = 0;
    *(rules + 7) = 0;
  }
}
