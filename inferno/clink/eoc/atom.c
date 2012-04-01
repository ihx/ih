#include "ih/inferno/clink/eoc/atom.h"
#include "ih/inferno/clink/system.h"
#include "ih/core/tools.h"

#define THINK_STRING_LENGTH 8

struct ih_inferno_clink_eoc_atom_t {
  ih_inferno_clink_system_t *clink;
  unsigned char last_char;
  char think_string[THINK_STRING_LENGTH];
  unsigned char think_string_read_position;
  unsigned char think_string_write_position;
};

static ih_core_bool_t think(ih_inferno_clink_system_t *system, void *object,
    void *context);
static int compare(void *char_a_object, void *char_b_object);
static void destroy(void *char_object);

int compare(void *char_a_object, void *char_b_object)
{
  assert(char_a_object);
  assert(char_b_object);
  char *a = char_a_object;
  char *b = char_b_object;
  int compare_result;

  if (*a < *b) {
    compare_result = -1;
  } else if (*a > *b) {
    compare_result = 1;
  } else {
    compare_result = 0;
  }

  return compare_result;
}

void destroy(void *char_object)
{
  assert(char_object);
  char *c = char_object;
  free(c);
}

ih_core_bool_t think(ih_inferno_clink_system_t *system, void *object, void *context)
{
  assert(system);
  assert(object);
  assert(context);
  char *c = object;
  ih_inferno_clink_eoc_atom_t *atom = context;

  *(atom->think_string + atom->think_string_write_position) = *c;
  atom->think_string_write_position++;
  if (THINK_STRING_LENGTH == atom->think_string_write_position) {
    atom->think_string_write_position = 0;
  }

  return ih_core_bool_true;
}

ih_inferno_clink_eoc_atom_t *ih_inferno_clink_eoc_atom_create(unsigned long max_concepts,
    unsigned long max_links)
{
  ih_inferno_clink_eoc_atom_t *atom;
  unsigned char i;

  atom = malloc(sizeof *atom);
  if (atom) {
    atom->last_char = '\0';
    for (i = 0; i < THINK_STRING_LENGTH; i++) {
      *(atom->think_string + i) = random() % 9;
    }
    atom->think_string_read_position = 0;
    atom->think_string_write_position = 0;
    atom->clink = ih_inferno_clink_system_create(max_concepts, max_links, compare,
        destroy, atom);
    if (!atom->clink) {
      ih_core_trace("x_clink_system_create");
      free(atom);
      atom = NULL;
    }
  } else {
    ih_core_trace("malloc");
  }

  return atom;
}

void ih_inferno_clink_eoc_atom_destroy(ih_inferno_clink_eoc_atom_t *atom)
{
  assert(atom);
  ih_inferno_clink_system_destroy(atom->clink);
  free(atom);
}

unsigned char ih_inferno_clink_eoc_atom_get_direction(ih_inferno_clink_eoc_atom_t *atom)
{
  assert(atom);
  unsigned char direction;

  direction = *(atom->think_string + atom->think_string_read_position);
  atom->think_string_read_position++;
  if (THINK_STRING_LENGTH == atom->think_string_read_position) {
    atom->think_string_read_position = 0;
  }

  return direction;
}

unsigned char ih_inferno_clink_eoc_atom_get_face(ih_inferno_clink_eoc_atom_t *atom)
{
  assert(atom);
  unsigned char face;

  face = *(atom->think_string + atom->think_string_read_position);
  atom->think_string_read_position++;
  if (THINK_STRING_LENGTH == atom->think_string_read_position) {
    atom->think_string_read_position = 0;
  }

  return face;
}

void *ih_inferno_clink_eoc_atom_get_linked_object(ih_inferno_clink_eoc_atom_t *atom,
    unsigned long concept_index, unsigned long object_index)
{
  assert(atom);
  return ih_inferno_clink_system_get_linked_object(atom->clink, concept_index,
      object_index);
}

void *ih_inferno_clink_eoc_atom_get_object(ih_inferno_clink_eoc_atom_t *atom,
    unsigned long concept_index)
{
  assert(atom);
  return ih_inferno_clink_system_get_object(atom->clink, concept_index);
}

void ih_inferno_clink_eoc_atom_observe(ih_inferno_clink_eoc_atom_t *atom, unsigned char c)
{
  assert(atom);
  char *current_char;
  char *last_char;

  current_char = malloc(sizeof *current_char);
  if (current_char) {
    last_char = malloc(sizeof *last_char);
    if (last_char) {
      *current_char = c;
      *last_char = atom->last_char;
      /* ih_inferno_clink_system_link(atom->clink, last_char, current_char); */
      ih_inferno_clink_system_link(atom->clink, current_char, last_char);
      if (*current_char == *last_char) {
        if (!ih_inferno_clink_system_think_tree
            (atom->clink, think, THINK_STRING_LENGTH, 3)) {
          ih_core_trace("x_clink_system_think_tree");
        }
      }
      atom->last_char = c;
    } else {
      ih_core_trace("malloc");
      free(current_char);
    }
  } else {
    ih_core_trace("malloc");
  }
}
