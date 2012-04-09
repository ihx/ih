#ifndef ih_case_shardset_h
#define ih_case_shardset_h

#include "ih/core/object.h"

#define IH_CASE_SHARDSET_MAX_SHARDS 32768

struct ih_case_shardset_t;
typedef struct ih_case_shardset_t ih_case_shardset_t;

ih_core_bool_t ih_case_shardset_add(ih_case_shardset_t *shardset,
    void *object);

ih_core_bool_t ih_case_shardset_add_replace(ih_case_shardset_t *shardset,
    void *object);

void ih_case_shardset_clear(ih_case_shardset_t *shardset);

ih_case_shardset_t *ih_case_shardset_create(ih_core_object_compare_f compare,
    ih_core_object_compare_equal_f compare_equal, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, ih_core_object_hash_f hash_object,
    ih_core_object_hash_f hash, unsigned short shard_count);

void ih_case_shardset_destroy(ih_case_shardset_t *shardset);

void *ih_case_shardset_find(ih_case_shardset_t *shardset, void *object);

void *ih_case_shardset_find_copy(ih_case_shardset_t *shardset, void *object);

unsigned long ih_case_shardset_get_size(ih_case_shardset_t *shardset);

void *ih_case_shardset_iterate_next(ih_case_shardset_t *shardset);

void ih_case_shardset_lock(ih_case_shardset_t *shardset);

void ih_case_shardset_iterate_remove(ih_case_shardset_t *shardset);

void ih_case_shardset_iterate_start(ih_case_shardset_t *shardset);

void ih_case_shardset_print(ih_case_shardset_t *shardset,
    ih_core_object_get_as_string_f get_object_as_string);

ih_core_bool_t ih_case_shardset_remove(ih_case_shardset_t *shardset,
    void *object);

unsigned long ih_case_shardset_remove_if(ih_case_shardset_t *shardset,
    ih_core_object_evaluate_condition_f object_condition);

void ih_case_shardset_unlock(ih_case_shardset_t *shardset);

#endif
