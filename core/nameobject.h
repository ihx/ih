#ifndef ih_core_nameobject_h
#define ih_core_nameobject_h

#include "ih/core/object.h"
#include "ih/core/iobject.h"

struct ih_core_nameobject_t;
typedef struct ih_core_nameobject_t ih_core_nameobject_t;

int ih_core_nameobject_compare(void *nameobject_object_a,
    void *nameobject_object_b);

ih_core_bool_t ih_core_nameobject_compare_equal(void *nameobject_a_object,
    void *nameobject_b_object);

void *ih_core_nameobject_copy(void *nameobject_object);

ih_core_nameobject_t *ih_core_nameobject_create(char *name, void *object,
    ih_core_object_copy_f copy, ih_core_object_destroy_f destroy,
    ih_core_object_get_as_string_f get_as_string);

ih_core_nameobject_t *ih_core_nameobject_create_decoy(char *name);

void ih_core_nameobject_destroy(void *nameobject_object);

void ih_core_nameobject_destroy_decoy(void *nameobject_object);

char *ih_core_nameobject_get_as_string(void *nameobject_object);

char *ih_core_nameobject_get_name(ih_core_nameobject_t *nameobject);

void *ih_core_nameobject_get_object(ih_core_nameobject_t *nameobject);

unsigned long ih_core_nameobject_hash(void *nameobject_object);

void ih_core_nameobject_init_iobject(ih_core_iobject_t *iobject);

void ih_core_nameobject_print(void *nameobject_object);

#endif
