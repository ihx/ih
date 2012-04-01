#include "ih/core/standard.h"
#include "ih/case/list.h"
#include "ih/core/string.h"

int main(int argc, char *argv[])
{
  ih_case_list_t *list;
  void *object;
  char *object_string;
  unsigned long index;
  unsigned long iteration;
  ih_case_list_t *strings;
  char *string;
  char *string_to_split;

  list = ih_case_list_create(ih_core_string_compare, ih_core_string_copy,
      ih_core_string_destroy);

  ih_case_list_add_first(list, strdup("puppy"));
  ih_case_list_add_first(list, strdup("rooster"));
  ih_case_list_add_first(list, strdup("cow"));
  ih_case_list_add_last(list, strdup("spots"));

  for (index = 0; index < 5; index++) {
    object = ih_case_list_find_at(list, index);
    if (object) {
      object_string = (char *) object;
      printf("%s\n", object_string);
    }
  }

  printf("\n");

  for (iteration = 0; iteration < 16; iteration++) {
    object = ih_case_list_find_random(list);
    if (object) {
      object_string = (char *) object;
      printf("%s\n", object_string);
    }
  }

  printf("\n");

  ih_case_list_iterate_start(list);
  while ((object = ih_case_list_iterate_next(list))) {
    object_string = (char *) object;
    printf("%s\n", object_string);
  }

  printf("\n");

  ih_case_list_iterate_start(list);
  while ((object = ih_case_list_iterate_next(list))) {
    object_string = (char *) object;
    printf("%s\n", object_string);
  }

  ih_case_list_destroy(list);

  ih_case_list_t *list2;
  list2 = ih_case_list_create(ih_core_string_compare, ih_core_string_copy,
      ih_core_string_destroy);
  ih_case_list_add_first(list2, malloc(7));
  ih_case_list_remove_first(list2);
  ih_case_list_destroy(list2);

  string_to_split = malloc(sizeof("here I am"));
  strcpy(string_to_split, "here I am");

  strings = ih_case_list_create_strings_from_string(string_to_split, " ");
  ih_case_list_iterate_start(strings);
  while ((string = ih_case_list_iterate_next(strings))) {
    printf(":%s:\n", string);
  }
  ih_case_list_destroy(strings);

  free(string_to_split);

  return 0;
}
