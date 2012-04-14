#ifndef ih_slug_h
#define ih_slug_h

#include "bitarray.h"
#include "cxbitarray.h"

ih_bit_t ih_slug_classify(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...);

void ih_slug_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules);

#endif
