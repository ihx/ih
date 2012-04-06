#include "ih/core/standard.h"
#include "ih/core/tools.h"
#include "ih/mg/system.h"

#define GOAL_TOTAL 256

unsigned short numbers[32] = {
  23, 123, 456, 235, 567, 123, 11, 89,
  213, 1, 76, 57, 78, 131, 411, 859,
  44, 45, 56, 315, 15, 126, 101, 889,
  243, 423, 356, 87, 192, 348, 45, 54
};

double calculate_fitness(uint32_t genome, void *context)
{
  double fitness;
  unsigned long total = 0;
  unsigned short i;
  unsigned short *numbers = context;
  unsigned short total_numbers = 0;

  for (i = 0; i < 32; i++) {
    if (ih_core_get_bit(genome, i)) {
      total += *(numbers + i);
      total_numbers++;
    }
  }

  /*  fitness = 1 / (1 + fabs(GOAL_TOTAL - total));  */
  fitness = (1 / (1 + fabs(GOAL_TOTAL - total))) / (1 + total_numbers);

  return fitness;
}

int main(int argc, char *argv[])
{
  ih_mg_system_t *minigen;
  uint32_t fittest_genome;
  unsigned short i;
  unsigned long total = 0;
  ih_core_bool_t first_number = ih_core_bool_true;

  minigen = ih_mg_system_create(calculate_fitness, numbers);
  if (!minigen) {
    ih_core_trace_exit("ih_mg_system_create");
  }

  fittest_genome = ih_mg_system_generate(minigen);
  for (i = 0; i < 32; i++) {
    if (ih_core_get_bit(fittest_genome, i)) {
      if (!first_number) {
        printf(" + ");
      }
      total += *(numbers + i);
      printf("%d", *(numbers + i));
      first_number = ih_core_bool_false;
    }
  }
  printf(" = %lu\n", total);

  ih_mg_system_destroy(minigen);

  return 0;
}
