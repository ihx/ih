#include "ih/inferno/clink/system.h"
#include "ih/core/tools.h"

#define MAX_CONCEPTS 5
#define MAX_LINKS 3

static int compare(void *char_a_object, void *char_b_object);
static char *get_as_string(void *char_object);
int main(int argc, char *argv[]);
static ih_core_bool_t think(ih_inferno_clink_system_t *clink, void *char_object,
    void *context);

int compare(void *char_a_object, void *char_b_object)
{
  assert(char_a_object);
  assert(char_b_object);
  char *a = char_a_object;
  char *b = char_b_object;
  int compare_result;

  if (*a < *b) {
    compare_result = -1;
  } else if (*a > *b) {
    compare_result = 1;
  } else {
    compare_result = 0;
  }

  return compare_result;
}

char *get_as_string(void *char_object)
{
  assert(char_object);
  char *string;
  char *c = char_object;

  string = malloc(2);
  if (string) {
    *(string + 0) = *c;
    *(string + 1) = '\0';
  } else {
    ih_core_trace("malloc");
  }

  return string;
}

int main(int argc, char *argv[])
{
  char *s = " It was the best of times, it was the worst of times.";
  /*  char *s = "ab";  */
  /*  char *s = "It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way - in short, the period was so far like the present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.";  */
  assert(strlen(s) > 1);
  ih_inferno_clink_system_t *clink;
  ih_inferno_clink_concept_t *concept;
  char *c;

  concept = NULL;

  clink = ih_inferno_clink_system_create(MAX_CONCEPTS, MAX_LINKS, compare,
      IH_CORE_OBJECT_NO_DESTROY_F, NULL);
  if (clink) {
    c = s + 1;
    while (*c) {
      ih_inferno_clink_system_link(clink, c - 1, c);
      printf("\n");
      ih_inferno_clink_system_print(clink, get_as_string);
      c++;
    }

    printf("\nthink::\n");
    /*  ih_inferno_clink_system_think_train(clink, think, 10);  */
    ih_inferno_clink_system_think_tree(clink, think, 32, 3);
    printf("--\n");

    ih_inferno_clink_system_destroy(clink);
  } else {
    ih_core_trace("x_clink_system_create");
  }

  return 0;
}

ih_core_bool_t think(ih_inferno_clink_system_t *clink, void *char_object, void *context)
{
  assert(clink);
  assert(char_object);
  char *c = char_object;

  printf("%c", *c);

  return ih_core_bool_true;
}
