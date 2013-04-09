#include "bit.h"
#include "boole.h"
#include "minigen.h"
#include "standard.h"
#include "trace.h"

#define CONVERGENCE_SAMPLE_SIZE 16               /*  sqrt(POPULATION_SIZE)  */
#define CONVERGENCE_THRESHOLD_DIVISOR 5
#define DIVERGE_MODULUS 2
#define POPULATION_SIZE 256

#define BURST_COUNT POPULATION_SIZE
#define MAX_MATINGS (POPULATION_SIZE * 1024)
#define MUTATION_MODULUS (POPULATION_SIZE / 4)

struct organism_t {
  ih_genome_t genome;
  double fitness;
  ih_boole_t fitness_is_valid;
};
typedef struct organism_t organism_t;

struct minigen_t {
  ih_fitness_calculate_f calculate_fitness;
  organism_t population[POPULATION_SIZE];
  double fittest_fitness;
  unsigned short fittest_organism_index;
  void *context;
};
typedef struct minigen_t minigen_t;

static unsigned short choose_child(minigen_t *minigen);
static unsigned short choose_parent(minigen_t *minigen);
static ih_boole_t converged(minigen_t *minigen, double required_fitness);
static void diverge(minigen_t *minigen);
static double get_fitness(minigen_t *minigen,
    unsigned short organism_index);
static void init(minigen_t *minigen,
    ih_fitness_calculate_f calculate_fitness, void *context);

unsigned short choose_child(minigen_t *minigen)
{
  unsigned short possible_a_index = random() % POPULATION_SIZE;
  unsigned short possible_b_index = random() % POPULATION_SIZE;
  unsigned short child_index;

  if (get_fitness(minigen, possible_a_index) <
      get_fitness(minigen, possible_b_index)) {
    child_index = possible_a_index;
  } else {
    child_index = possible_b_index;
  }

  return child_index;
}

unsigned short choose_parent(minigen_t *minigen)
{
  unsigned short possible_a_index = random() % POPULATION_SIZE;
  unsigned short possible_b_index = random() % POPULATION_SIZE;
  unsigned short parent_index;

  if (get_fitness(minigen, possible_a_index) >
      get_fitness(minigen, possible_b_index)) {
    parent_index = possible_a_index;
  } else {
    parent_index = possible_b_index;
  }

  return parent_index;
}

ih_boole_t converged(minigen_t *minigen, double required_fitness)
{
  double max_fitness = 0.0;
  double min_fitness = 1.0;
  unsigned short i;
  unsigned short organism_index;
  double fitness;
  ih_boole_t converged;

  for (i = 0; i < CONVERGENCE_SAMPLE_SIZE; i++) {
    organism_index = random() % POPULATION_SIZE;
    fitness = get_fitness(minigen, organism_index);
    if (fitness > max_fitness) {
      max_fitness = fitness;
    }
    if (fitness < min_fitness) {
      min_fitness = fitness;
    }
  }

  if (fabs(max_fitness - min_fitness)
      < (required_fitness / CONVERGENCE_THRESHOLD_DIVISOR)) {
    converged = ih_boole_true;
  } else {
    converged = ih_boole_false;
  }

  return converged;
}

void diverge(minigen_t *minigen)
{
  unsigned short i;
  organism_t *organism;

  for (i = 0; i < POPULATION_SIZE; i++) {
    if (i != minigen->fittest_organism_index) {
      if (0 == (random() % DIVERGE_MODULUS)) {
        organism = minigen->population + i;
        ih_bitarray_randomize(&organism->genome);
        organism->fitness_is_valid = ih_boole_false;
      }
    }
  }
}

double get_fitness(minigen_t *minigen, unsigned short organism_index)
{
  organism_t *organism = minigen->population + organism_index;

  if (!organism->fitness_is_valid) {
    organism->fitness = minigen->calculate_fitness(organism->genome,
        minigen->context);
    if (organism->fitness > minigen->fittest_fitness) {
      minigen->fittest_fitness = organism->fitness;
      minigen->fittest_organism_index = organism_index;
    }
    organism->fitness_is_valid = ih_boole_true;
  }

  return organism->fitness;
}

ih_genome_t ih_minigen_evolve
(ih_fitness_calculate_f calculate_fitness, double required_fitness,
    void *context)
{
  unsigned short parent_a_index;
  unsigned short parent_b_index;
  unsigned short child_index;
  organism_t *parent_a;
  organism_t *parent_b;
  organism_t *child;
  unsigned short i;
  unsigned short cut_point;
  unsigned short j;
  unsigned long mating_count = 0;
  minigen_t minigen;

  init(&minigen, calculate_fitness, context);

  while ((minigen.fittest_fitness < required_fitness)
      && (mating_count < MAX_MATINGS)) {
    if (converged(&minigen, required_fitness)) {
      diverge(&minigen);
    }
    for (j = 0; j < BURST_COUNT; j++) {
      parent_a_index = choose_parent(&minigen);
      parent_b_index = choose_parent(&minigen);
      child_index = choose_child(&minigen);
      parent_a = minigen.population + parent_a_index;
      parent_b = minigen.population + parent_b_index;
      child = minigen.population + child_index;
      cut_point = random() % IH_GENOME_SIZE_BITS;
      for (i = 0; i < cut_point; i++) {
        ih_bit_set(&child->genome, i, ih_bit_get(parent_a->genome, i));
      }
      for (i = cut_point; i < IH_GENOME_SIZE_BITS; i++) {
        ih_bit_set(&child->genome, i, ih_bit_get(parent_b->genome, i));
      }
      if (0 == (random() % MUTATION_MODULUS)) {
        ih_bit_set(&child->genome, random() % IH_GENOME_SIZE_BITS,
            random() % 2);
      }
      child->fitness_is_valid = ih_boole_false;
      mating_count++;
    }
    /*  printf("+");  */
  }
  /*  printf("\n");  */

  return (minigen.population + minigen.fittest_organism_index)->genome;
}

void init(minigen_t *minigen, ih_fitness_calculate_f calculate_fitness,
    void *context) {
  unsigned short i;
  organism_t *organism;

  minigen->calculate_fitness = calculate_fitness;
  for (i = 0; i < POPULATION_SIZE; i++) {
    organism = minigen->population + i;
    ih_bitarray_randomize(&organism->genome);
    organism->fitness_is_valid = ih_boole_false;
  }
  minigen->fittest_fitness = 0.0;
  minigen->fittest_organism_index = 0;
  minigen->context = context;
  srandom(time(NULL));
}
