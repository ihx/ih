#ifndef ih_inferno_clink_concept_h
#define ih_inferno_clink_concept_h

#include "ih/core/object.h"

struct ih_inferno_clink_concept_t;
typedef struct ih_inferno_clink_concept_t ih_inferno_clink_concept_t;

ih_inferno_clink_concept_t *ih_inferno_clink_concept_create(void *concept,
    unsigned long max_links, ih_core_object_compare_f compare,
    ih_core_object_destroy_f destroy);

void ih_inferno_clink_concept_destroy(ih_inferno_clink_concept_t *concept);

void *ih_inferno_clink_concept_get_linked_object(ih_inferno_clink_concept_t *concept,
    unsigned long link_index);

void *ih_inferno_clink_concept_get_object(ih_inferno_clink_concept_t *concept);

void ih_inferno_clink_concept_note_object(ih_inferno_clink_concept_t *concept, void *object);

void ih_inferno_clink_concept_print(ih_inferno_clink_concept_t *concept,
    ih_core_object_get_as_string_f get_as_string);

#endif
