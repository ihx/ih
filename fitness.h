#ifndef ih_fitness_h
#define ih_fitness_h

#include "genome.h"

typedef double (*ih_fitness_calculate_f)(ih_genome_t genome, void *context);
/*  must return a double >=0.0 and <=1.0  */

#endif
