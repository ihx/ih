#include "ih/core/bool.h"
#include "ih/core/objects.h"
#include "ih/core/pair.h"
#include "ih/core/standard.h"
#include "ih/core/string.h"
#include "ih/core/tools.h"
#include "ih/core/uuid.h"
#include "ih/core/basic/long.h"
#include "ih/core/basic/unsigned_long.h"
#include "ih/core/basic/void.h"

static ih_core_bool_t initialized = ih_core_bool_false;

void ih_core_objects_init()
{
  if (!initialized) {
    ih_core_basic_long_init_iobject(&ih_core_objects.long_iobject);
    ih_core_pair_init_iobject(&ih_core_objects.pair_iobject);
    ih_core_string_init_iobject(&ih_core_objects.string_iobject);
    ih_core_basic_unsigned_long_init_iobject
      (&ih_core_objects.unsigned_long_iobject);
    ih_core_uuid_init_iobject(&ih_core_objects.uuid_iobject);
    ih_core_basic_void_init_iobject(&ih_core_objects.void_iobject);
    initialized = ih_core_bool_true;
  } else {
    ih_core_trace("fyi :: ih_core_objects_init called more than once");
  }
}
