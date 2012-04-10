#include "ih/inferno/clink/system.h"
#include "ih/core/tools.h"

#define MAX_CONCEPTS 8
#define MAX_LINKS 4

static int compare(void *char_a_object, void *char_b_object);
static void destroy(void *char_object);
static char *get_as_string(void *char_object);
int main(int argc, char *argv[]);

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

void destroy(void *char_object)
{
  assert(char_object);
  char *c = char_object;
  free(c);
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
  ih_disable_test();

  ih_inferno_clink_system_t *clink;
  char current_char = ' ';
  char last_char = ' ';
  char *current_object;
  char *last_object;


  clink = ih_inferno_clink_system_create(MAX_CONCEPTS, MAX_LINKS, compare,
      destroy, NULL);
  if (clink) {
    while ((current_char = getc(stdin))) {
      if ('\n' == current_char) {
        continue;
      }
      current_object = malloc(sizeof(*current_object));
      if (current_object) {
        *current_object = current_char;
        last_object = malloc(sizeof(*last_object));
        if (last_object) {
          *last_object = last_char;
          ih_inferno_clink_system_link(clink, last_object, current_object);
          printf("\n");
          ih_inferno_clink_system_print(clink, get_as_string);
          last_char = current_char;
        } else {
          ih_core_trace("malloc");
          free(current_object);
          break;
        }
      } else {
        ih_core_trace("malloc");
        break;
      }
    }
    ih_inferno_clink_system_destroy(clink);
  } else {
    ih_core_trace("x_clink_system_create");
  }

  return 0;
}
