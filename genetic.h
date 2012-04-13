#ifndef ih_genetic_h
#define ih_genetic_h

#include "fitness.h"
#include "genome.h"

#define IH_GENETIC_NO_REQUIRED_FITNESS -1.0

struct ih_genetic_t;
typedef struct ih_genetic_t ih_genetic_t;

ih_genetic_t *ih_genetic_create(ih_fitness_calculate_f calculate_fitness,
    void *context, ih_genome_t *initial_genomes);
void ih_genetic_destroy(ih_genetic_t *genetic);
ih_genome_t *ih_genetic_get_genomes(ih_genetic_t *genetic);
void ih_genetic_evolve(ih_genetic_t *genetic, double required_fitness,
    ih_genome_t *genome, double *fitness);

#endif
