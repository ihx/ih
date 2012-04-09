#include "ih/case/list.h"
#include "ih/core/imessage.h"
#include "ih/core/log.h"
#include "ih/core/tools.h"
#include "ih/net/engine/iengine.h"
#include "ih/net/pingpong/engine.h"
#include "ih/net/pingpong/message.h"
#include "ih/net/post/ipost.h"
#include "ih/net/post/system.h"
#include "ih/net/server/system.h"

#define PING_SERVER_MAX_THREADS 32

struct ping_server_context_t {
  void *server_wide_shared_database;
};
typedef struct ping_server_context_t ping_server_context_t;

static void print_use_exit();

void print_use_exit()
{
  printf("\n    use: ping_server server_port\n\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  ih_net_server_system_t *server;
  ping_server_context_t custom_server_context;
  unsigned short server_port;
  ih_net_engine_iengine_t iengine;
  ih_core_imessage_t messagey;
  ih_net_post_ipost_t ipost;
  ih_core_log_t *log;

  if (argc < 2) {
    print_use_exit();
  }
  server_port = atoi(argv[1]);

  log = ih_core_log_create(stdout);
  if (!log) {
    ih_core_trace_exit("x_audit_log_create");
  }

  ih_net_engine_iengine_init(&iengine, ih_pingpong_engine_create,
      ih_pingpong_engine_destroy, ih_pingpong_engine_get_handler_for_message,
      ih_pingpong_engine_maintain, ih_pingpong_engine_run,
      ih_pingpong_engine_start, ih_pingpong_engine_stop);

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

  server = ih_net_server_system_create("ping", server_port, server_port,
      PING_SERVER_MAX_THREADS, &messagey, &ipost,
      IH_NET_SERVER_SYSTEM_NO_CONFIG_SYSTEM, log);
  if (!server) {
    ih_core_trace_exit("x_net_server_create");
  }

  if (!ih_net_server_system_register_engine(server, IH_CORE_ENGINE_PING,
          &custom_server_context, &iengine, 2, 2, IH_NET_MAINTAIN_1_MINUTE,
          IH_PINGPONG_MESSAGE_TYPE_COUNT)) {
    ih_core_trace_exit("x_net_server_register_engine");
  }

  if (!ih_net_server_system_start(server)) {
    ih_core_trace_exit("x_net_server_start");
  }

  ih_net_server_system_destroy(server);
  ih_core_log_destroy(log);

  return 0;
}
