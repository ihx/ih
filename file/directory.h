#ifndef ih_file_directory_h
#define ih_file_directory_h

#include "ih/core/standard.h"
#include "ih/core/bool.h"

struct ih_file_directory_t;
typedef struct ih_file_directory_t ih_file_directory_t;

ih_file_directory_t *ih_file_directory_create();

void ih_file_directory_destroy(ih_file_directory_t *ih_file_directory);

ih_core_bool_t ih_file_directory_exists(char *directory_name);

ih_core_bool_t ih_file_directory_make(char *directory_name, mode_t mode);

#endif
