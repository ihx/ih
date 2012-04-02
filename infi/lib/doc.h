#ifndef ih_infi_lib_doc_h
#define ih_infi_lib_doc_h

#include "ih/core/uuid.h"

struct ih_infi_lib_doc_t;
typedef struct ih_infi_lib_doc_t ih_infi_lib_doc_t;

ih_infi_lib_doc_t *ih_infi_lib_doc_create();
void ih_infi_lib_doc_destroy(ih_infi_lib_doc_t *doc);
ih_core_bitarray_t *ih_infi_lib_doc_get_text(ih_infi_lib_doc_t *doc);

#endif
