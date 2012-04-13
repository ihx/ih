#ifndef ih_tube_h
#define ih_tube_h

#include "bitarray.h"
#include "cxbitarray.h"

void ih_tube_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules);

#endif
