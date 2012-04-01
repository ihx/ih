#include "ih/inferno/memory/system.h"
#include "ih/core/tools.h"

struct ih_inferno_memory_system_t {
};

ih_core_bool_t ih_inferno_memory_system_add(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary)
{
  return ih_core_bool_false;
}

ih_inferno_memory_system_t *ih_inferno_memory_system_create(unsigned long node_count,
    unsigned short link_density)
{
  ih_inferno_memory_system_t *system;

  system = malloc(sizeof *system);
  if (system) {

  } else {
    ih_core_trace("malloc");
  }

  return system;
}

void ih_inferno_memory_system_destroy(ih_inferno_memory_system_t *system)
{
  assert(system);
  free(system);
}

ih_core_bool_t ih_inferno_memory_system_find(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary)
{
  return ih_core_bool_false;
}

ih_case_array_t *ih_inferno_memory_system_find_cloud(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long cloud_size_max)
{
  return NULL;
}

ih_core_bool_t ih_inferno_memory_system_remove(ih_inferno_memory_system_t *system,
    unsigned long base, unsigned long link, unsigned long corollary)
{
  return ih_core_bool_false;
}
