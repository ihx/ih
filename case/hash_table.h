#ifndef ih_case_hash_table_h
#define ih_case_hash_table_h

#include "ih/core/object.h"
#include "ih/core/iobject.h"
#include "ih/core/tools.h"

struct ih_case_hash_table_t;
typedef struct ih_case_hash_table_t ih_case_hash_table_t;

ih_core_bool_t ih_case_hash_table_add(ih_case_hash_table_t *hash_table,
    void *object);

void ih_case_hash_table_clear(ih_case_hash_table_t *hash_table);

ih_case_hash_table_t *ih_case_hash_table_create(ih_core_iobject_t *iobject);

void ih_case_hash_table_destroy(ih_case_hash_table_t *hash_table);

void ih_case_hash_table_dont_destroy_objects(ih_case_hash_table_t *hash_table);

void *ih_case_hash_table_find(ih_case_hash_table_t *hash_table,
    void *decoy_object);

ih_core_iobject_t *ih_case_hash_table_get_iobject
(ih_case_hash_table_t *hash_table);

unsigned long ih_case_hash_table_get_size(ih_case_hash_table_t *hash_table);

void ih_case_hash_table_iterate_remove(ih_case_hash_table_t *hash_table);

void ih_case_hash_table_iterate_start(ih_case_hash_table_t *hash_table);

void *ih_case_hash_table_iterate_next(ih_case_hash_table_t *hash_table);

ih_core_bool_t ih_case_hash_table_remove(ih_case_hash_table_t *hash_table,
    void *decoy_object);

#endif
