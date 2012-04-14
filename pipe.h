#ifndef ih_pipe_h
#define ih_pipe_h

#include "bitarray.h"
#include "cxbitarray.h"

ih_bit_t ih_pipe_classify(ih_bitarray_t bitarray, ih_classify_style_t style,
    unsigned short rule_count, ...);

void ih_pipe_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned char *rules);

#endif
