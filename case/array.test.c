#include "ih/case/array.h"
#include "ih/core/standard.h"
#include "ih/core/string.h"

int main(int argc, char *argv[])
{
  ih_case_array_t *array;
  void *object;
  char *object_string;
  unsigned long index;
  unsigned long iteration;

  array = ih_case_array_create(4, ih_core_string_compare,
      ih_core_string_copy, ih_core_string_destroy);

  ih_case_array_add(array, 0, strdup("puppy"));
  ih_case_array_add(array, 1, strdup("rooster"));
  ih_case_array_add(array, 2, strdup("cow"));
  ih_case_array_add(array, 3, strdup("spots"));

  for (index = 0; index < 4; index++) {
    object = ih_case_array_find(array, index);
    if (object) {
      object_string = (char *) object;
      printf("%s\n", object_string);
    }
  }

  printf("\n");

  for (iteration = 0; iteration < 16; iteration++) {
    object = ih_case_array_find_random(array);
    if (object) {
      object_string = (char *) object;
      printf("%s\n", object_string);
    }
  }

  printf("\n");

  ih_case_array_iterate_start(array);
  while ((object = ih_case_array_iterate_next(array))) {
    object_string = (char *) object;
    printf("%s\n", object_string);
  }

  printf("\n");

  ih_case_array_iterate_start(array);
  while ((object = ih_case_array_iterate_next(array))) {
    object_string = (char *) object;
    printf("%s\n", object_string);
  }

  ih_case_array_destroy(array);

  ih_case_array_t *array2;
  array2 = ih_case_array_create(1, ih_core_string_compare,
      ih_core_string_copy, ih_core_string_destroy);
  ih_case_array_add(array2, 0, malloc(7));
  ih_case_array_remove(array2, 0);
  ih_case_array_destroy(array2);

  return 0;
}
