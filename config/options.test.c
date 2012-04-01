#include "ih/config/options.h"
#include "ih/core/tools.h"

#define DEFAULT_MODE "modex"
#define DEFAULT_OPTION "optionx"

int main(int argc, char *argv[])
{
  ih_config_options_t *options;
  char *value;

  ih_core_objects_init();

  options = ih_config_options_create(argc, argv, &ih_core_objects);
  if (!options) {
    ih_core_trace_exit("x_config_options_create");
  }

  if (ih_config_options_find_as_string(options, "mode", &value, DEFAULT_MODE)) {
    printf(":%s:\n", value);
  } else {
  }

  if (ih_config_options_find_as_string
      (options, "option", &value, DEFAULT_OPTION)) {
    printf(":%s:\n", value);
  } else {
  }

  ih_config_options_destroy(options);

  return 0;
}
