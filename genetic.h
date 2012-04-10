#ifndef ih_genetic_h
#define ih_genetic_h

#include "genome.h"
#include "standard.h"

struct ih_genetic_t;
typedef struct ih_genetic_t ih_genetic_t;

typedef double (*ih_genetic_calculate_fitness_f)(ih_genome_t genome,
    void *context);
/*  must return a double >=0.0 and <=1.0  */

ih_genetic_t *ih_genetic_create
(ih_genetic_calculate_fitness_f calculate_fitness, double required_fitness,
    void *context);

void ih_genetic_destroy(ih_genetic_t *system);

ih_genome_t ih_genetic_generate(ih_genetic_t *system);

#endif
