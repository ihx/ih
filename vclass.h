#ifndef ih_vclass_h
#define ih_vclass_h

#include "bitarray.h"
#include "cxbitarray.h"

void ih_vclass_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, double required_fitness,
    ih_classify_style_t classify_style, unsigned long *rules);

#endif
