#include "ih/core/engine.h"
#include "ih/core/message.h"
#include "ih/core/imessage.h"
#include "ih/core/tools.h"
#include "ih/net/test/engine.h"
#include "ih/net/test/message.h"

ih_core_message_t *ih_net_test_message_create(int client_socket,
    unsigned long message_type)
{
  return ih_core_message_create(client_socket, IH_CORE_ENGINE_TEST,
      message_type, IH_CORE_IMESSAGE_NULL_DATA,
      IH_CORE_IMESSAGE_ZERO_DATA_SIZE);
}
