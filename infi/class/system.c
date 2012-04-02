#include "ih/infi/class/system.h"
#include "ih/core/standard.h"

struct ih_infi_class_system_t {
};

ih_core_bit_t ih_infi_class_system_classify(ih_core_uuid_t *subject)
{
  return ih_core_bit_zero;
}

ih_infi_class_system_t *ih_infi_class_system_create()
{
  return NULL;
}

void ih_infi_class_system_destroy(ih_infi_class_system_t *system)
{
}

void ih_infi_class_system_feedback(ih_core_uuid_t *subject, double grade)
{
}
