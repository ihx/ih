#ifndef ih_minigen_h
#define ih_minigen_h

#include "genome.h"
#include "standard.h"

struct ih_minigen_t;
typedef struct ih_minigen_t ih_minigen_t;

typedef double (*ih_minigen_calculate_fitness_f)(ih_genome_t genome,
    void *context);
/*  must return a double >=0.0 and <=1.0  */

ih_minigen_t *ih_minigen_create
(ih_minigen_calculate_fitness_f calculate_fitness, double required_fitness,
    void *context);

void ih_minigen_destroy(ih_minigen_t *system);

ih_genome_t ih_minigen_generate(ih_minigen_t *system);

#endif
