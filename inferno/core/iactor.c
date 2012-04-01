#include "ih/inferno/core/iactor.h"
#include "ih/core/standard.h"

void ih_inferno_core_iactor_free(ih_inferno_core_iactor_t *iactor) {}

void ih_inferno_core_iactor_init(ih_inferno_core_iactor_t *iactor,
    ih_inferno_core_iactor_create_f create,
    ih_inferno_core_iactor_create_random_f create_random,
    ih_core_object_compare_f compare, ih_core_object_copy_f copy,
    ih_core_object_destroy_f destroy, ih_core_object_get_object_f get_box_cell,
    ih_core_object_set_object_f set_box_cell)
{
  assert(iactor);

  iactor->create = create;
  iactor->create_random = create_random;
  iactor->compare = compare;
  iactor->copy = copy;
  iactor->destroy = destroy;
  iactor->get_box_cell = get_box_cell;
  iactor->set_box_cell = set_box_cell;
}
