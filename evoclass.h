#ifndef ih_evoclass_h
#define ih_evoclass_h

#include "bitarray.h"
#include "cxbitarray.h"

void ih_evoclass_evolve(ih_cxbitarray_t *cxbitarrays,
    unsigned long cxbitarrays_size, unsigned long *rules);

#endif
