#include "ih/core/imessage.h"
#include "ih/core/standard.h"

void ih_core_imessage_init(ih_core_imessage_t *messagey,
    ih_core_imessage_destroy_f destroy,
    ih_core_imessage_get_client_socket_f get_client_socket,
    ih_core_imessage_get_engine_id_f get_engine_id,
    ih_core_imessage_get_type_f get_type)
{
  assert(messagey);

  messagey->destroy = destroy;
  messagey->get_client_socket = get_client_socket;
  messagey->get_engine_id = get_engine_id;
  messagey->get_type = get_type;
}
