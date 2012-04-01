#include "ih/case/set.h"
#include "ih/core/basic/unsigned_long.h"
#include "ih/core/tools.h"
#include "ih/core/uuid.h"

#define ITERATIONS 10000
#define TEST_USING_LONGS ih_core_bool_true

static void print_uuid(ih_core_uuid_t *uuid, const char *name);

static void print_uuid(ih_core_uuid_t *uuid, const char *name)
{
  assert(uuid);
  assert(name);
  char *uuid_string;

  uuid_string = ih_core_uuid_get_string(uuid);
  printf("%s=:%s:\n", name, uuid_string);
}

int main(int argc, char *argv[])
{
  ih_case_set_t *set;
  long *l;
  unsigned long n;
  unsigned long items_added;
  ih_core_uuid_t *uuid;
  ih_core_iobject_t unsigned_long_iobject;
  ih_core_iobject_t uuid_iobject;

  printf("creating set...\n");
  if (TEST_USING_LONGS) {
    ih_core_basic_unsigned_long_init_iobject(&unsigned_long_iobject);
    set = ih_case_set_create(&unsigned_long_iobject);
  } else {
    ih_core_basic_unsigned_long_init_iobject(&uuid_iobject);
    set = ih_case_set_create(&uuid_iobject);
  }
  assert(set);

  printf("adding to set...\n");
  items_added = 0;
  for (n = 0; n < ITERATIONS; n++) {
    if (TEST_USING_LONGS) {
      l = malloc(sizeof *l);
      *l = random() % ITERATIONS;
      if (ih_case_set_add(set, l)) {
        items_added++;
      } else {
        ih_core_basic_unsigned_long_destroy(l);
      }
    } else {
      uuid = ih_core_uuid_create();
      if (ih_core_bool_false) {
        print_uuid(uuid, "uuid");
      }
      if (ih_case_set_add(set, uuid)) {
        items_added++;
      } else {
        ih_core_uuid_destroy(uuid);
      }
    }
  }
  printf("items added: %lu\n", items_added);
  printf("set size: %lu\n", ih_case_set_get_size(set));

  printf("removing from set...\n");
  for (n = 0; n < ITERATIONS; n++) {
    if (TEST_USING_LONGS) {
      l = malloc(sizeof *l);
      *l = random() % ITERATIONS;
      ih_case_set_remove(set, l);
      free(l);
    }
  }
  printf("set size: %lu\n", ih_case_set_get_size(set));

  if (ih_core_bool_false) {
    printf("doing iterate_remove on the rest of the set\n");
    ih_case_set_iterate_start(set);
    if (TEST_USING_LONGS) {
      while ((l = ih_case_set_iterate_next(set))) {
        ih_case_set_iterate_remove(set);
      }
    } else {
      while ((uuid = ih_case_set_iterate_next(set))) {
        ih_case_set_iterate_remove(set);
      }
    }
    printf("set size: %lu\n", ih_case_set_get_size(set));
    assert(0 == ih_case_set_get_size(set));
  }

  printf("clearing set...\n");
  ih_case_set_clear(set);
  printf("set size: %lu\n", ih_case_set_get_size(set));
  assert(0 == ih_case_set_get_size(set));

  printf("destroying set...\n");
  ih_case_set_destroy(set);

  return 0;
}
