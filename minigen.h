#ifndef ih_minigen_h
#define ih_minigen_h

#include "fitness.h"
#include "genome.h"
#include "standard.h"

ih_genome_t ih_minigen_evolve(ih_fitness_calculate_f calculate_fitness,
    double required_fitness, void *context);

#endif
