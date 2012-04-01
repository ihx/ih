#include "ih/inferno/mind/system.h"
#include "ih/core/tools.h"

struct ih_inferno_mind_system_t {
};

ih_inferno_mind_system_t *ih_inferno_mind_system_create()
{
  ih_inferno_mind_system_t *system;

  system = malloc(sizeof *system);
  if (system) {

  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_inferno_mind_system_destroy(ih_inferno_mind_system_t *system)
{
  assert(system);
  free(system);
}
