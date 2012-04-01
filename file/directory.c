#include "ih/file/directory.h"
#include "ih/core/tools.h"

struct ih_file_directory_t {};

ih_file_directory_t *ih_file_directory_create()
{
  return NULL;
}

void ih_file_directory_destroy(ih_file_directory_t *ih_file_directory)
{
}

ih_core_bool_t ih_file_directory_exists(char *directory_name)
{
  assert(directory_name);
  ih_core_bool_t exists;
  DIR *dir;

  dir = opendir(directory_name);
  if (dir) {
    exists = ih_core_bool_true;
    if (0 != closedir(dir)) {
      ih_core_trace("closedir");
    }
  } else {
    exists = ih_core_bool_false;
  }

  return exists;
}

ih_core_bool_t ih_file_directory_make(char *directory_name, mode_t mode)
{
  assert(directory_name);
  ih_core_bool_t success;

  if (0 == mkdir(directory_name, mode)) {
    success = ih_core_bool_true;
  } else {
    success = ih_core_bool_false;
  }

  return success;
}
