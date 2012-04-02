#ifndef ih_chage_atom_h
#define ih_chage_atom_h

#include "ih/chage/sing/system.h"
#include "ih/chage/tools.h"
#include "ih/core/tools.h"

struct ih_chage_atom_t;
typedef struct ih_chage_atom_t ih_chage_atom_t;

ih_chage_atom_t *ih_chage_atom_create(ih_chage_atom_t *container);

void ih_chage_atom_destroy(ih_chage_atom_t *atom);

ih_chage_atom_t *ih_chage_atom_get_contained(ih_chage_atom_t *atom,
    position_t position);

ih_chage_atom_t *ih_chage_atom_get_container(ih_chage_atom_t *atom);

ih_core_bool_t ih_chage_atom_spark(ih_chage_atom_t *atom);

ih_core_bool_t ih_chage_atom_spark_distance(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired);

#endif
