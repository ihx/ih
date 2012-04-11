#ifndef ih_minigen_h
#define ih_minigen_h

#include "genome.h"
#include "standard.h"

typedef double (*ih_minigen_calculate_fitness_f)(ih_genome_t genome,
    void *context);
/*  must return a double >=0.0 and <=1.0  */

ih_genome_t ih_minigen_evolve(ih_minigen_calculate_fitness_f calculate_fitness,
    double required_fitness, void *context);

#endif
