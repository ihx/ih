#include "ih/core/message.h"
#include "ih/core/imessage.h"
#include "ih/seq/engine.h"
#include "ih/seq/message.h"

ih_core_message_t *ih_seq_message_create(int client_socket,
    unsigned long message_type)
{
  return ih_core_message_create(client_socket, IH_CORE_ENGINE_SEQ,
      message_type, IH_CORE_IMESSAGE_NULL_DATA,
      IH_CORE_IMESSAGE_ZERO_DATA_SIZE);
}
