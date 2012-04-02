#ifndef ih_infi_class_system_h
#define ih_infi_class_system_h

#include "ih/core/bit.h"
#include "ih/core/uuid.h"

struct ih_infi_class_system_t;
typedef struct ih_infi_class_system_t ih_infi_class_system_t;

ih_core_bit_t ih_infi_class_system_classify(ih_core_uuid_t *subject);
ih_infi_class_system_t *ih_infi_class_system_create();
void ih_infi_class_system_destroy(ih_infi_class_system_t *system);
void ih_infi_class_system_feedback(ih_core_uuid_t *subject, double grade);

#endif
