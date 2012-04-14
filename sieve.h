#ifndef ih_sieve_h
#define ih_sieve_h

#include "bit.h"
#include "bitarray.h"
#include "classify.h"
#include "cxbitarray.h"

ih_bit_t ih_sieve_classify(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned char rule_0, unsigned char rule_1, unsigned char rule_2,
    unsigned char rule_3, unsigned char rule_4, unsigned char rule_5,
    unsigned char rule_6, unsigned char rule_7);

void ih_sieve_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned char *rules);

#endif
