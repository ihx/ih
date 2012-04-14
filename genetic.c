#include "bit.h"
#include "boole.h"
#include "genetic.h"
#include "trace.h"
#include "wrap.h"

#define BACKWASH_MODULUS 32
#define BLOWTHROUGH_MODULUS 2
#define CONVERGENCE_THRESHOLD_DIVISOR 5
#define DIRECTION_GENE 0
#define DIVERGE_MODULUS 2
#define MAX_MOVE 4
#define MUTATION_MODULUS 1024
#define WORLD_DIMENSION IH_BITARRAY_SIZE

#define BURST_COUNT (WORLD_DIMENSION * WORLD_DIMENSION * 4)
#define CONVERGENCE_SAMPLE_SIZE WORLD_DIMENSION
#define MAX_EVOLUTIONS WORLD_DIMENSION * WORLD_DIMENSION * 32768

struct direction_t;
typedef struct direction_t direction_t;

struct organism_t;
typedef struct organism_t organism_t;

struct position_t;
typedef struct position_t position_t;

struct direction_t {
  char x;
  char y;
};

struct organism_t {
  ih_genome_t genome;
  double fitness;
  ih_boole_t fitness_is_valid;
};

struct position_t {
  unsigned short x;
  unsigned short y;
};

struct ih_genetic_t {
  ih_fitness_calculate_f calculate_fitness;
  organism_t population[WORLD_DIMENSION][WORLD_DIMENSION];
  double fittest_fitness;
  position_t fittest_organism_position;
  double required_fitness;
  void *context;
};

static void calculate_new_position(ih_genetic_t *genetic, organism_t *organism,
    position_t *current_position, direction_t *direction,
    position_t *new_position);
static ih_boole_t converged(ih_genetic_t *genetic);
static void diverge(ih_genetic_t *genetic);
static void evolve(ih_genetic_t *genetic);
static void get_direction(organism_t *organism, direction_t *direction);
static double get_fitness(ih_genetic_t *genetic, position_t position);
static void meet(organism_t *organism, organism_t *target_organism);
static void move(ih_genetic_t *genetic, position_t *position_a,
    position_t *position_b);

void calculate_new_position(ih_genetic_t *genetic, organism_t *organism,
    position_t *current_position, direction_t *direction,
    position_t *new_position)
{
  double fitness = get_fitness(genetic, *current_position);
  new_position->x = ih_wrap(current_position->x
      + (direction->x * fitness * (random() % MAX_MOVE)), WORLD_DIMENSION);
  new_position->y = ih_wrap(current_position->y
      + (direction->y * fitness * (random() % MAX_MOVE)), WORLD_DIMENSION);
}

static ih_boole_t converged(ih_genetic_t *genetic)
{
  double max_fitness = 0.0;
  double min_fitness = 1.0;
  unsigned short i;
  position_t organism_position;
  double fitness;
  ih_boole_t converged;

  for (i = 0; i < CONVERGENCE_SAMPLE_SIZE; i++) {
    organism_position.x = random() % WORLD_DIMENSION;
    organism_position.y = random() % WORLD_DIMENSION;
    fitness = get_fitness(genetic, organism_position);
    if (fitness > max_fitness) {
      max_fitness = fitness;
    }
    if (fitness < min_fitness) {
      min_fitness = fitness;
    }
  }

  if (fabs(max_fitness - min_fitness)
      < (genetic->required_fitness / CONVERGENCE_THRESHOLD_DIVISOR)) {
    converged = ih_boole_true;
  } else {
    converged = ih_boole_false;
  }

  return converged;
}

void diverge(ih_genetic_t *genetic)
{
  unsigned short x;
  unsigned short y;
  organism_t *organism;

  for (x = 0; x < WORLD_DIMENSION; x++) {
    for (y = 0; y < WORLD_DIMENSION; y++) {
      if (!(x == genetic->fittest_organism_position.x
              && y == genetic->fittest_organism_position.y)) {
        if (0 == (random() % DIVERGE_MODULUS)) {
          organism = &genetic->population[x][y];
          ih_bitarray_randomize(&organism->genome);
          organism->fitness_is_valid = ih_boole_false;
        }
      }
    }
  }
}

void evolve(ih_genetic_t *genetic)
{
  unsigned short x = random() % WORLD_DIMENSION;
  unsigned short y = random() % WORLD_DIMENSION;
  position_t current_position;
  organism_t *organism = &genetic->population[x][y];
  direction_t direction;
  organism_t *target_organism;
  position_t new_position;
  double fitness;
  double target_fitness;

  current_position.x = x;
  current_position.y = y;

  get_direction(organism, &direction);
  calculate_new_position(genetic, organism, &current_position, &direction,
      &new_position);
  target_organism = &genetic->population[new_position.x][new_position.y];
  fitness = get_fitness(genetic, current_position);
  target_fitness = get_fitness(genetic, new_position);
  if (fitness > target_fitness) {
    meet(organism, target_organism);
    move(genetic, &current_position, &new_position);
  }
}

void get_direction(organism_t *organism, direction_t *direction)
{
  unsigned char x_gene_mod_3 = ih_bitarray_get_uint8(&organism->genome,
      DIRECTION_GENE) % 3;
  unsigned char y_gene_mod_3 = ih_bitarray_get_uint8(&organism->genome,
      DIRECTION_GENE + 8) % 3;

  if (0 == x_gene_mod_3) {
    direction->x = -1;
  } else if (1 == x_gene_mod_3) {
    direction->x = 0;
  } else {
    direction->x = 1;
  }
  if (0 == y_gene_mod_3) {
    direction->y = -1;
  } else if (1 == y_gene_mod_3) {
    direction->y = 0;
  } else {
    direction->y = 1;
  }
}

double get_fitness(ih_genetic_t *genetic, position_t position)
{
  organism_t *organism = &genetic->population[position.x][position.y];

  if (!organism->fitness_is_valid) {
    organism->fitness = genetic->calculate_fitness(organism->genome,
        genetic->context);
    if (organism->fitness > genetic->fittest_fitness) {
      genetic->fittest_fitness = organism->fitness;
      genetic->fittest_organism_position = position;
    }
    organism->fitness_is_valid = ih_boole_true;
  }

  return organism->fitness;
}

ih_genetic_t *ih_genetic_create(ih_fitness_calculate_f calculate_fitness,
    void *context, ih_genome_t *initial_genomes)
{
  ih_genetic_t *genetic;
  unsigned short x;
  unsigned short y;
  organism_t *organism;

  genetic = malloc(sizeof *genetic);
  if (genetic) {
    genetic->calculate_fitness = calculate_fitness;
    genetic->context = context;
    for (x = 0; x < WORLD_DIMENSION; x++) {
      for (y = 0; y < WORLD_DIMENSION; y++) {
        organism = &genetic->population[x][y];
        ih_bitarray_randomize(&organism->genome);
        organism->fitness_is_valid = ih_boole_false;
      }
    }
    genetic->fittest_fitness = 0.0;
    genetic->fittest_organism_position.x = 0;
    genetic->fittest_organism_position.y = 0;
    srandom(time(NULL));
  } else {
    ih_trace("malloc");
  }

  return genetic;
}

void ih_genetic_destroy(ih_genetic_t *genetic)
{
  free(genetic);
}

ih_genome_t *ih_genetic_get_genomes(ih_genetic_t *genetic)
{
  return NULL;
}

void ih_genetic_evolve(ih_genetic_t *genetic, double required_fitness,
    ih_genome_t *genome, double *fitness)
{
  unsigned short i;
  unsigned long evolution_count = 0;

  if (IH_GENETIC_NO_REQUIRED_FITNESS == required_fitness) {
    if (converged(genetic)) {
      diverge(genetic);
    }
    for (i = 0; i < BURST_COUNT; i++) {
      evolve(genetic);
    }
  } else {
    while ((genetic->fittest_fitness < required_fitness)
        && (evolution_count < MAX_EVOLUTIONS)) {
      if (converged(genetic)) {
        diverge(genetic);
      }
      for (i = 0; i < BURST_COUNT; i++) {
        evolve(genetic);
        evolution_count++;
      }
    }
  }

  *genome = genetic->population[genetic->fittest_organism_position.x]
    [genetic->fittest_organism_position.y].genome;
  *fitness = genetic->fittest_fitness;
}

void meet(organism_t *organism, organism_t *target_organism)
{
  unsigned char i;

  for (i = 0; i < IH_BITARRAY_SIZE; i++) {
    if (0 == (random() % BLOWTHROUGH_MODULUS)) {
      ih_bit_set(&target_organism->genome, i, ih_bit_get(organism->genome, i));
    } else if (0 == (random() % BACKWASH_MODULUS)) {
      ih_bit_set(&organism->genome, i, ih_bit_get(target_organism->genome, i));
      organism->fitness_is_valid = ih_boole_false;
    }
  }
  target_organism->fitness_is_valid = ih_boole_false;
}

void move(ih_genetic_t *genetic, position_t *position_a,
    position_t *position_b)
{
  organism_t temp_organism;

  /*
    this is messy and could be alleviated by a higher-level redesign in terms
    of where and how the positions are stored, and how the organisms are stored
  */
  if (genetic->fittest_organism_position.x == position_a->x
      && genetic->fittest_organism_position.y == position_a->y) {
    genetic->fittest_organism_position.x = position_b->x;
    genetic->fittest_organism_position.y = position_b->y;
  } else if (genetic->fittest_organism_position.x == position_b->x
      && genetic->fittest_organism_position.y == position_b->y) {
    genetic->fittest_organism_position.x = position_a->x;
    genetic->fittest_organism_position.y = position_a->y;
  }

  temp_organism = genetic->population[position_b->x][position_b->y];
  genetic->population[position_b->x][position_b->y]
    = genetic->population[position_a->x][position_a->y];
  genetic->population[position_a->x][position_a->y] = temp_organism;
}
