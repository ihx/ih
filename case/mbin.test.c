#include "ih/case/mbin.h"
#include "ih/core/basic/unsigned_long.h"
#include "ih/core/tools.h"
#include "ih/core/uuid.h"

#define ITERATIONS 10000
#define TEST_USING_LONGS ih_core_bool_false

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
  ih_case_mbin_t *mbin;
  long *l;
  unsigned long n;
  unsigned long items_added;
  ih_core_uuid_t *uuid;
  ih_core_iobject_t iobject;

  printf("creating mbin...\n");
  if (TEST_USING_LONGS) {
    ih_core_basic_unsigned_long_init_iobject(&iobject);
    mbin = ih_case_mbin_create(&iobject, IH_CASE_MBIN_SET_TYPE_SET);
  } else {
    ih_core_uuid_init_iobject(&iobject);
    mbin = ih_case_mbin_create(&iobject, IH_CASE_MBIN_SET_TYPE_SET);
  }
  assert(mbin);

  printf("adding to mbin...\n");
  items_added = 0;
  for (n = 0; n < ITERATIONS; n++) {
    if (TEST_USING_LONGS) {
      l = malloc(sizeof *l);
      *l = random() % ITERATIONS;
      if (ih_case_mbin_add(mbin, l)) {
        /*  printf("added %lu\n", *l);  */
        items_added++;
      } else {
        ih_core_basic_unsigned_long_destroy(l);
      }
    } else {
      uuid = ih_core_uuid_create();
      if (ih_core_bool_false) {
        print_uuid(uuid, "uuid");
      }
      if (ih_case_mbin_add(mbin, uuid)) {
        items_added++;
      } else {
        ih_core_uuid_destroy(uuid);
      }
    }
  }
  printf("items added: %lu\n", items_added);
  printf("mbin size: %lu\n", ih_case_mbin_get_size(mbin));

  printf("removing from mbin...\n");
  for (n = 0; n < ITERATIONS; n++) {
    if (TEST_USING_LONGS) {
      l = malloc(sizeof *l);
      *l = random() % ITERATIONS;
      ih_case_mbin_remove(mbin, l);
      /*  printf("removed %lu\n", *l);  */
      free(l);
    }
  }
  printf("mbin size: %lu\n", ih_case_mbin_get_size(mbin));

  if (ih_core_bool_false) {
    printf("doing iterate_remove on the rest of the mbin\n");
    ih_case_mbin_iterate_start(mbin);
    if (TEST_USING_LONGS) {
      while ((l = ih_case_mbin_iterate_next(mbin))) {
        ih_case_mbin_iterate_remove(mbin);
      }
    } else {
      while ((uuid = ih_case_mbin_iterate_next(mbin))) {
        ih_case_mbin_iterate_remove(mbin);
      }
    }
    printf("mbin size: %lu\n", ih_case_mbin_get_size(mbin));
    assert(0 == ih_case_mbin_get_size(mbin));
  }

  printf("clearing mbin...\n");
  ih_case_mbin_clear(mbin);
  printf("mbin size: %lu\n", ih_case_mbin_get_size(mbin));
  assert(0 == ih_case_mbin_get_size(mbin));

  printf("destroying mbin...\n");
  ih_case_mbin_destroy(mbin);

  return 0;
}
