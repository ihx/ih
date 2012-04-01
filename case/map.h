#ifndef ih_case_map_h
#define ih_case_map_h

#include "ih/core/bool.h"
#include "ih/core/object.h"
#include "ih/core/iobject.h"

#define IH_CASE_MAP_DESTROY ih_core_bool_true
#define IH_CASE_MAP_DONT_DESTROY ih_core_bool_false

struct ih_case_map_t;
typedef struct ih_case_map_t ih_case_map_t;

ih_core_bool_t ih_case_map_add(ih_case_map_t *map, void *left, void *right);

int ih_case_map_compare(void *map_object_a, void *map_object_b);

void *ih_case_map_copy(void *map_object);

ih_case_map_t *ih_case_map_create(ih_core_iobject_t *left_iobject,
    ih_core_iobject_t *right_iobject, ih_core_bool_t destroys);

void ih_case_map_destroy(void *map_object);

void *ih_case_map_find(ih_case_map_t *map, void *left_object_decoy);

void ih_case_map_print(ih_case_map_t *map);

ih_core_bool_t ih_case_map_remove(ih_case_map_t *map, void *left_object_decoy);

#endif
