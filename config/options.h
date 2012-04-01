#ifndef ih_config_options_h
#define ih_config_options_h

#include "ih/case/list.h"
#include "ih/core/objects.h"

struct ih_config_options_t;
typedef struct ih_config_options_t ih_config_options_t;

ih_config_options_t *ih_config_options_create(int argc, char *argv[],
    ih_core_objects_t *objects);

void ih_config_options_destroy(ih_config_options_t *options);

ih_core_bool_t ih_config_options_find(ih_config_options_t *options,
    char *name);

ih_core_bool_t ih_config_options_find_as_double(ih_config_options_t *options,
    char *name, double *value, double default_value);

ih_core_bool_t ih_config_options_find_as_string(ih_config_options_t *options,
    char *name, char **value, char *default_value);

ih_core_bool_t ih_config_options_find_as_unsigned_short
(ih_config_options_t *options, char *name, unsigned short *value,
    unsigned short default_value);

ih_core_bool_t ih_config_options_find_as_unsigned_long
(ih_config_options_t *options, char *name, unsigned long *value,
    unsigned long default_value);

ih_core_bool_t ih_config_options_find_list_as_strings
(ih_config_options_t *options, char *name, ih_case_list_t **list);

#endif
