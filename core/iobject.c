#include "ih/core/standard.h"
#include "ih/core/iobject.h"

void ih_core_iobject_init(ih_core_iobject_t *iobject,
    ih_core_object_compare_f compare,
    ih_core_object_compare_equal_f compare_equal,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy,
    ih_core_object_get_as_string_f get_as_string, ih_core_object_hash_f hash)
{
  assert(iobject);

  iobject->compare = compare;
  iobject->compare_equal = compare_equal;
  iobject->copy = copy;
  iobject->destroy = destroy;
  iobject->get_as_string = get_as_string;
  iobject->hash = hash;
}
