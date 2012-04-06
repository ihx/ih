#include "ih/core/tools.h"
#include "ih/mg/system.h"

#define CONVERGENCE_SAMPLE_SIZE 16               /*  sqrt(POPULATION_SIZE)  */
#define CONVERGENCE_THRESHOLD 0.2
#define DIVERGE_MODULUS 2
#define POPULATION_SIZE 256
#define REQUIRED_FITNESS 0.8

#define BURST_COUNT POPULATION_SIZE
#define MAX_MATINGS (POPULATION_SIZE * 1024)
#define MUTATION_MODULUS (POPULATION_SIZE / 4)

struct organism_t {
  uint32_t genome;
  double fitness;
  ih_core_bool_t fitness_is_valid;
};
typedef struct organism_t organism_t;

struct ih_mg_system_t {
  ih_mg_calculate_fitness_f calculate_fitness;
  organism_t population[POPULATION_SIZE];
  double fittest_fitness;
  unsigned short fittest_organism_index;
  void *context;
  ih_core_bool_t run_once;
};

static unsigned short choose_child(ih_mg_system_t *system);
static unsigned short choose_parent(ih_mg_system_t *system);
static ih_core_bool_t converged(ih_mg_system_t *system);
static void diverge(ih_mg_system_t *system);
static double get_fitness(ih_mg_system_t *system,
    unsigned short organism_index);
static void randomize_genome(uint32_t *genome);

unsigned short choose_child(ih_mg_system_t *system)
{
  assert(system);
  unsigned short possible_a_index = random() % POPULATION_SIZE;
  unsigned short possible_b_index = random() % POPULATION_SIZE;
  unsigned short child_index;

  if (get_fitness(system, possible_a_index) <
      get_fitness(system, possible_b_index)) {
    child_index = possible_a_index;
  } else {
    child_index = possible_b_index;
  }

  return child_index;
}

unsigned short choose_parent(ih_mg_system_t *system)
{
  assert(system);
  unsigned short possible_a_index = random() % POPULATION_SIZE;
  unsigned short possible_b_index = random() % POPULATION_SIZE;
  unsigned short parent_index;

  if (get_fitness(system, possible_a_index) >
      get_fitness(system, possible_b_index)) {
    parent_index = possible_a_index;
  } else {
    parent_index = possible_b_index;
  }

  return parent_index;
}

static ih_core_bool_t converged(ih_mg_system_t *system)
{
  assert(system);
  double max_fitness = 0.0;
  double min_fitness = 1.0;
  unsigned short i;
  unsigned short organism_index;
  double fitness;
  ih_core_bool_t converged;

  for (i = 0; i < CONVERGENCE_SAMPLE_SIZE; i++) {
    organism_index = random() % POPULATION_SIZE;
    fitness = get_fitness(system, organism_index);
    if (fitness > max_fitness) {
      max_fitness = fitness;
    }
    if (fitness < min_fitness) {
      min_fitness = fitness;
    }
  }

  if (fabs(max_fitness - min_fitness) < CONVERGENCE_THRESHOLD) {
    converged = ih_core_bool_true;
  } else {
    converged = ih_core_bool_false;
  }

  return converged;
}

void diverge(ih_mg_system_t *system)
{
  unsigned short i;
  organism_t *organism;

  for (i = 0; i < POPULATION_SIZE; i++) {
    if (i != system->fittest_organism_index) {
      if (0 == (random() % DIVERGE_MODULUS)) {
        organism = system->population + i;
        randomize_genome(&organism->genome);
      }
    }
  }
}

double get_fitness(ih_mg_system_t *system, unsigned short organism_index)
{
  assert(system);
  organism_t *organism = system->population + organism_index;

  if (!organism->fitness_is_valid) {
    organism->fitness = system->calculate_fitness(organism->genome,
        system->context);
    if (organism->fitness > system->fittest_fitness) {
      system->fittest_fitness = organism->fitness;
      system->fittest_organism_index = organism_index;
    }
  }

  return organism->fitness;
}

ih_mg_system_t *ih_mg_system_create
(ih_mg_calculate_fitness_f calculate_fitness, void *context)
{
  assert(calculate_fitness);
  ih_mg_system_t *system;
  unsigned short i;
  organism_t *organism;

  system = malloc(sizeof *system);
  if (system) {
    system->calculate_fitness = calculate_fitness;
    for (i = 0; i < POPULATION_SIZE; i++) {
      organism = system->population + i;
      randomize_genome(&organism->genome);
      organism->fitness_is_valid = ih_core_bool_false;
    }
    system->fittest_fitness = 0.0;
    system->fittest_organism_index = 0;
    system->context = context;
    system->run_once = ih_core_bool_false;
    srandom(time(NULL));
  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_mg_system_destroy(ih_mg_system_t *system)
{
  free(system);
}

uint32_t ih_mg_system_generate(ih_mg_system_t *system)
{
  unsigned short parent_a_index = choose_parent(system);
  unsigned short parent_b_index = choose_parent(system);
  unsigned short child_index = choose_child(system);
  organism_t *parent_a = system->population + parent_a_index;
  organism_t *parent_b = system->population + parent_b_index;
  organism_t *child = system->population + child_index;
  unsigned short i;
  unsigned short cut_point;
  unsigned short j;
  unsigned long mating_count = 0;

  if (!system->run_once) {
    while ((system->fittest_fitness < REQUIRED_FITNESS)
        && (mating_count < MAX_MATINGS)) {
      if (converged(system)) {
        diverge(system);
      }
      for (j = 0; j < BURST_COUNT; j++) {
        cut_point = random() % 32;
        for (i = 0; i < cut_point; i++) {
          ih_core_set_bit(&child->genome, i,
              ih_core_get_bit(parent_a->genome, i));
        }
        for (i = cut_point; i < 32; i++) {
          ih_core_set_bit(&child->genome, i,
              ih_core_get_bit(parent_b->genome, i));
        }
        if (0 == (random() % MUTATION_MODULUS)) {
          ih_core_set_bit(&child->genome, random() % 32, random() % 2);
        }
        mating_count++;
      }
      /*  printf("+");  */
    }
    /*  printf("\n");  */
    system->run_once = ih_core_bool_true;
  } else {
    ih_core_trace_exit("ih_mg_system_generate() has already been run for "
        "this system.  only call this function once per system.");
  }

  return (system->population + system->fittest_organism_index)->genome;
}

void randomize_genome(uint32_t *genome)
{
  assert(genome);
  unsigned short i;

  for (i = 0; i < 32; i++) {
    ih_core_set_bit(genome, i, random() % 2);
  }
}
