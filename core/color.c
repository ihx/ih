#include "ih/core/standard.h"
#include "ih/core/color.h"

void ih_core_color_init(ih_core_color_t *color, unsigned long red,
    unsigned long blue, unsigned long green)
{
  assert(color);

  color->red = red;
  color->green = green;
  color->blue = blue;
}
