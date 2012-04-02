#include "ih/core/bitarray.h"
#include "ih/core/standard.h"
#include "ih/infi/lib/doc.h"

struct ih_infi_lib_doc_t {
  ih_core_uuid_t *subject;
  ih_core_bitarray_t *text;
};

ih_infi_lib_doc_t *ih_infi_lib_doc_create()
{
  return NULL;
}

void ih_infi_lib_doc_destroy(ih_infi_lib_doc_t *doc)
{
}

ih_core_bitarray_t *ih_infi_lib_doc_get_text(ih_infi_lib_doc_t *doc)
{
  return doc->text;
}
