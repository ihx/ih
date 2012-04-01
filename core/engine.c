#include "ih/core/engine.h"

static char *engine_names[IH_CORE_ENGINE_TYPE_COUNT] = {
  "void",
  "test",
  "ping",
  "shell",
  "http",
  "seq",
  "lib",
  "class"
};

char *ih_core_engine_get_name(unsigned long engine_id)
{
  char *engine_name;

  if (engine_id < IH_CORE_ENGINE_TYPE_COUNT) {
    engine_name = engine_names[engine_id];
  } else {
    engine_name = "[unknown]";
  }

  return engine_name;
}
