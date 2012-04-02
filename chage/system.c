#include "ih/chage/system.h"
#include "ih/chage/atom.h"

struct ih_chage_system_t {
  ih_chage_atom_t *universe;
  ih_chage_atom_t *focus;
};

ih_chage_system_t *ih_chage_system_create()
{
  ih_chage_system_t *system;

  system = malloc(sizeof *system);
  if (system) {
    system->universe = ih_chage_atom_create(NULL);
    if (system->universe) {
      system->focus = system->universe;
    } else {
      ih_core_trace("chage_atom_create");
      free(system);
      system = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_chage_system_destroy(ih_chage_system_t *system)
{
  assert(system);
  ih_chage_atom_destroy(system->universe);
  free(system);
}

void ih_chage_system_spark(ih_chage_system_t *system)
{
  assert(system);
  ih_chage_interval_t start_interval;
  ih_chage_interval_t interval;
  ih_core_bool_t interval_expired = ih_core_bool_false;
  unsigned long target_distance = 0;
  unsigned long actual_distance = 0;

  start_interval = ih_chage_determine_interval();
  do {
    if (!ih_chage_atom_spark_distance
        (system->focus, target_distance, actual_distance, start_interval,
            &interval_expired)) {
      ih_core_trace("chage_atom_spark_distance");
    }
    target_distance++;
    interval = ih_chage_determine_interval();
    if (interval != start_interval) {
      interval_expired = ih_core_bool_true;
    }
  } while (!interval_expired);
}
