#include "ih/core/content.h"

static char *content_names[IH_CORE_CONTENT_TYPE_COUNT] = {
  "void",
  "image/gif",
  "teih/css",
  "teih/html",
  "teih/javascript"
};

char *ih_core_content_get_name(ih_core_content_t content_type)
{
  char *content_name;

  if (content_type < IH_CORE_CONTENT_TYPE_COUNT) {
    content_name = content_names[content_type];
  } else {
    content_name = "[unknown]";
  }

  return content_name;
}
