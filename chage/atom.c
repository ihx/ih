#include "ih/chage/atom.h"

struct ih_chage_atom_t {
  ih_chage_atom_t *container;
  ih_chage_atom_t **contained;
  ih_chage_interval_t last_sparked_in_interval;
};

static ih_core_bool_t spark_distance_contained(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired);

static ih_core_bool_t spark_distance_container(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired);

static ih_core_bool_t spark_distance_peers(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired);

ih_chage_atom_t *ih_chage_atom_create(ih_chage_atom_t *container)
{
  ih_chage_atom_t *atom;

  atom = malloc(sizeof *atom);
  if (atom) {
    atom->container = container;
    atom->contained = NULL;
    atom->last_sparked_in_interval = IH_CHAGE_INTERVAL_VOID;
  } else {
    ih_core_trace("malloc");
  }

  return atom;
}

void ih_chage_atom_destroy(ih_chage_atom_t *atom)
{
  assert(atom);
  free(atom);
}

ih_chage_atom_t *ih_chage_atom_get_contained(ih_chage_atom_t *atom, position_t position)
{
  return NULL;
}

ih_chage_atom_t *ih_chage_atom_get_container(ih_chage_atom_t *atom)
{
  return atom->container;
}

ih_core_bool_t ih_chage_atom_spark(ih_chage_atom_t *atom)
{
  assert(atom);

  /*  printf("sparking %p\n", atom);  */
  atom->last_sparked_in_interval = ih_chage_determine_interval();

  return ih_core_bool_true;
}

ih_core_bool_t ih_chage_atom_spark_distance(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired)
{
  assert(atom);
  assert(interval_expired);
  ih_core_bool_t success = ih_core_bool_true;
  ih_chage_interval_t interval;

  if (target_distance != actual_distance) {

    if (!spark_distance_container(atom, target_distance, actual_distance,
            start_interval, interval_expired)) {
      success = ih_core_bool_false;
      ih_core_trace("spark_distance_container");
    }
    if (*interval_expired) {
      return success;
    }

    if (!spark_distance_contained(atom, target_distance, actual_distance,
            start_interval, interval_expired)) {
      success = ih_core_bool_false;
      ih_core_trace("spark_distance_contained");
    }
    if (*interval_expired) {
      return success;
    }

    if (!spark_distance_peers(atom, target_distance, actual_distance,
            start_interval, interval_expired)) {
      success = ih_core_bool_false;
      ih_core_trace("spark_distance_peers");
    }
    if (*interval_expired) {
      return success;
    }

  } else {
    if (atom->last_sparked_in_interval != start_interval) {
      if (!ih_chage_atom_spark(atom)) {
        success = ih_core_bool_false;
        ih_core_trace("chage_atom_spark");
      }
      interval = ih_chage_determine_interval();
      if (interval != start_interval) {
        *interval_expired = ih_core_bool_true;
      }
    }
  }

  return success;
}

ih_core_bool_t spark_distance_contained(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired)
{
  assert(atom);
  assert(interval_expired);
  ih_core_bool_t success = ih_core_bool_true;
  ih_chage_atom_t *contained_atom;
  unsigned short i;

  if (atom->contained) {
    for (i = 0; i < IH_CHAGE_CONTAINED_ATOMS; i++) {
      contained_atom = *(atom->contained + i);
      if (contained_atom) {
        if (!ih_chage_atom_spark_distance(contained_atom, target_distance,
                actual_distance + 1, start_interval, interval_expired)) {
          success = ih_core_bool_false;
          ih_core_trace("chage_atom_spark_distance");
        }
        if (*interval_expired) {
          break;
        }
      }
    }
  }

  return success;
}

ih_core_bool_t spark_distance_container(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired)
{
  assert(atom);
  assert(interval_expired);
  ih_core_bool_t success = ih_core_bool_true;

  if (atom->container) {
    if (!ih_chage_atom_spark_distance(atom->container, target_distance,
            actual_distance + 1, start_interval, interval_expired)) {
      success = ih_core_bool_false;
      ih_core_trace("chage_atom_spark_distance");
    }
  }

  return success;
}

ih_core_bool_t spark_distance_peers(ih_chage_atom_t *atom,
    unsigned long target_distance, unsigned long actual_distance,
    ih_chage_interval_t start_interval, ih_core_bool_t *interval_expired)
{
  assert(atom);
  assert(interval_expired);
  ih_core_bool_t success = ih_core_bool_true;

  if (atom->container) {
    if (!spark_distance_contained(atom->container, target_distance,
            actual_distance, start_interval, interval_expired)) {
      success = ih_core_bool_false;
      ih_core_trace("spark_distance_contained");
    }
  }

  return success;
}
