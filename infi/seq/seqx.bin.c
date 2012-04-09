#include "ih/config/tools.h"
#include "ih/case/list.h"
#include "ih/core/log.h"
#include "ih/core/tools.h"
#include "ih/net/engine/iengine.h"
#include "ih/net/http/message.h"
#include "ih/net/http/post.h"
#include "ih/net/post/system.h"
#include "ih/net/server/system.h"
#include "ih/infi/seq/engine.h"
#include "ih/infi/seq/message.h"

#define SEQX_SERVER_MAX_THREADS 8

struct ih_infi_seq_seqx_server_context_t {};
typedef struct ih_infi_seq_seqx_server_context_t ih_infi_seq_seqx_server_context_t;

int main(int argc, char *argv[])
{
  ih_config_disable_if_running_batch_tests(argc, argv);

  ih_infi_seq_seqx_server_context_t custom_server_context;
  ih_net_server_system_t *server;
  unsigned short port;
  ih_net_engine_iengine_t iengine;
  ih_core_imessage_t messagey;
  ih_net_post_ipost_t ipost;
  ih_core_log_t *log;

  log = ih_core_log_create(stdout);
  if (!log) {
    ih_core_trace_exit("ih_core_log_create");
  }

  port = 2881;

  ih_net_engine_iengine_init(&iengine, ih_infi_seq_engine_create,
      ih_infi_seq_engine_destroy, ih_infi_seq_engine_get_handler_for_message,
      ih_infi_seq_engine_maintain, ih_infi_seq_engine_run, ih_infi_seq_engine_start,
      ih_infi_seq_engine_stop);

  ih_core_imessage_init(&messagey, ih_core_message_destroy,
      ih_core_message_get_client_socket, ih_core_message_get_engine_id,
      ih_core_message_get_type);

  ih_net_post_ipost_init(&ipost, ih_net_post_system_compare,
      ih_net_post_system_create, ih_net_post_system_create_decoy,
      ih_net_post_system_destroy, ih_net_post_system_destroy_decoy,
      ih_net_post_system_get_last_receive_activity_time,
      ih_net_post_system_get_socket, ih_net_post_system_get_stats,
      ih_net_post_system_receive_message, ih_net_post_system_receive_messages,
      ih_net_post_system_send_message, ih_net_post_system_send_messages,
      ih_net_post_system_is_socket_closed, ih_net_post_system_hash,
      ih_net_post_system_compare_equal);

  server = ih_net_server_system_create("seqx", port, port,
      SEQX_SERVER_MAX_THREADS, &messagey, &ipost,
      IH_NET_SERVER_SYSTEM_NO_CONFIG_SYSTEM, log);

  if (!ih_net_server_system_register_engine(server, IH_CORE_ENGINE_SEQ,
          &custom_server_context, &iengine, 2, 2, IH_NET_MAINTAIN_1_MINUTE,
          IH_INFI_SEQ_MESSAGE_TYPE_COUNT)) {
    ih_core_trace_exit("x_net_server_register_engine");
  }

  if (!ih_net_server_system_start(server)) {
    ih_core_trace_exit("x_net_server_start");
  }

  ih_net_server_system_destroy(server);
  ih_core_log_destroy(log);

  return 0;
}
