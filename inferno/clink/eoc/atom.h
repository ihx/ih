#ifndef ih_inferno_clink_eoc_atom_h
#define ih_inferno_clink_eoc_atom_h

struct ih_inferno_clink_eoc_atom_t;
typedef struct ih_inferno_clink_eoc_atom_t ih_inferno_clink_eoc_atom_t;

ih_inferno_clink_eoc_atom_t *ih_inferno_clink_eoc_atom_create(unsigned long max_concepts,
    unsigned long max_links);

void ih_inferno_clink_eoc_atom_destroy(ih_inferno_clink_eoc_atom_t *atom);

unsigned char ih_inferno_clink_eoc_atom_get_direction(ih_inferno_clink_eoc_atom_t *atom);

unsigned char ih_inferno_clink_eoc_atom_get_face(ih_inferno_clink_eoc_atom_t *atom);

void *ih_inferno_clink_eoc_atom_get_linked_object(ih_inferno_clink_eoc_atom_t *atom,
    unsigned long concept_index, unsigned long object_index);

void *ih_inferno_clink_eoc_atom_get_object(ih_inferno_clink_eoc_atom_t *atom,
    unsigned long concept_index);

void ih_inferno_clink_eoc_atom_observe(ih_inferno_clink_eoc_atom_t *atom, unsigned char c);

#endif
