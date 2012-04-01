#ifndef ih_inferno_clink_system_h
#define ih_inferno_clink_system_h

#include "ih/inferno/clink/concept.h"
#include "ih/core/bool.h"

struct ih_inferno_clink_system_t;
typedef struct ih_inferno_clink_system_t ih_inferno_clink_system_t;

typedef ih_core_bool_t (*ih_inferno_clink_system_think_f)(ih_inferno_clink_system_t *system,
    void *object, void *context);

ih_inferno_clink_system_t *ih_inferno_clink_system_create(unsigned long max_concepts,
    unsigned long max_links, ih_core_object_compare_f compare,
    ih_core_object_destroy_f destroy, void *context);

void ih_inferno_clink_system_destroy(ih_inferno_clink_system_t *system);

ih_inferno_clink_concept_t *ih_inferno_clink_system_get_concept(ih_inferno_clink_system_t *system,
    unsigned long concept_index);

ih_core_bool_t ih_inferno_clink_system_get_index(ih_inferno_clink_system_t *system, void *object,
    unsigned long *index);

void *ih_inferno_clink_system_get_linked_object(ih_inferno_clink_system_t *system,
    unsigned long concept_index, unsigned long link_index);

void *ih_inferno_clink_system_get_object(ih_inferno_clink_system_t *system,
    unsigned long concept_index);

void ih_inferno_clink_system_link(ih_inferno_clink_system_t *system, void *object_a,
    void *object_b);

void ih_inferno_clink_system_print(ih_inferno_clink_system_t *system,
    ih_core_object_get_as_string_f get_as_string);

ih_core_bool_t ih_inferno_clink_system_think_train(ih_inferno_clink_system_t *system,
    ih_inferno_clink_system_think_f think, unsigned long max_objects);

ih_core_bool_t ih_inferno_clink_system_think_tree(ih_inferno_clink_system_t *system,
    ih_inferno_clink_system_think_f think, unsigned long max_objects,
    unsigned long branch_density);

#endif
