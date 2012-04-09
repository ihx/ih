#include "ih/case/shardset.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"

#define SHARD_COUNT IH_CASE_SHARDSET_MAX_SHARDS

int main(int argc, char *argv[])
{
  ih_case_shardset_t *shardset;
  char *string;

  shardset = ih_case_shardset_create(ih_core_string_compare,
      ih_core_string_compare_equal, ih_core_string_copy,
      IH_CORE_OBJECT_NO_DESTROY_F, ih_core_string_hash,
      ih_core_string_hash, SHARD_COUNT);
  if (!shardset) {
    ih_core_trace_exit("x_case_shardset_create");
  }

  ih_case_shardset_add(shardset, "apple");
  ih_case_shardset_add(shardset, "bicycle");
  ih_case_shardset_add(shardset, "color");

  ih_case_shardset_iterate_start(shardset);
  while ((string = ih_case_shardset_iterate_next(shardset))) {
    printf("%s\n", string);
    if (0 == strcmp("bicycle", string)) {
      ih_case_shardset_iterate_remove(shardset);
    }
  }

  printf("\n");

  ih_case_shardset_iterate_start(shardset);
  while ((string = ih_case_shardset_iterate_next(shardset))) {
    printf("%s\n", string);
  }

  return 0;
}
