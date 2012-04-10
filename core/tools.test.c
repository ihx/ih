#include "ih/core/tools.h"

#define REPETITIONS 32768

int main(int argc, char *argv[])
{
  unsigned long each_toss;
  /*  unsigned short toss_result;  */
  unsigned short i;
  uint32_t value32;

  if (ih_core_bool_false) {
    printf("tossing a coin %d times\n", REPETITIONS);
    for (each_toss = 0; each_toss < REPETITIONS; each_toss++) {
      /*  toss_result = ih_core_toss_coin();  */
    }
  }

  value32 = 0;
  ih_core_set_bit(&value32, 3, 1);
  ih_core_set_bit(&value32, 5, 1);
  ih_core_set_bit(&value32, 6, 1);
  for (i = 0; i < 32; i++) {
    printf("%d", ih_core_get_bit(value32, i));
  }
  printf("\n");

  return 0;
}
