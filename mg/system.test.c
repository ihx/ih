#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/mg/system.h"

double calculate_fitness(uint32_t genome)
{
  double fitness;

  if ((0 == (genome % 17)) && (0 == (genome % 37))) {
    fitness = 1.0;
  } else if (0 == (genome % 17)) {
    fitness = 0.5;
  } else {
    fitness = (random() % 256) / 1024.0;
  }

  return fitness;
}

int main(int argc, char *argv[])
{
  ih_mg_system_t *minigen;
  uint32_t fittest_genome;

  minigen = ih_mg_system_create(calculate_fitness);
  if (!minigen) {
    ih_core_trace_exit("ih_mg_system_create");
  }

  fittest_genome = ih_mg_system_generate(minigen);
  printf("%lu\n", (unsigned long) fittest_genome);

  ih_mg_system_destroy(minigen);

  return 0;
}
