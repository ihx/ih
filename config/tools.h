#ifndef ih_config_tools_h
#define ih_config_tools_h

#include "ih/core/bool.h"

void ih_config_disable_if_running_batch_tests(int argc, char *argv[]);

ih_core_bool_t ih_config_running_batch_tests(int argc, char *argv[]);

#endif
