#include "ih/case/list.h"
#include "ih/config/tools.h"
#include "ih/core/log.h"
#include "ih/core/tools.h"
#include "ih/net/engine/iengine.h"
#include "ih/net/http/message.h"
#include "ih/net/http/post.h"
#include "ih/net/post/system.h"
#include "ih/net/server/system.h"
#include "ih/net/test/engine.h"
#include "ih/net/test/http/engine.h"
#include "ih/net/test/message.h"

#define TEST_SERVER_MAX_THREADS 32
#define TEST_HTTP_SERVER_MAX_THREADS 32

struct ih_core_test_server_context_t {
  void *server_wide_shared_database;
};
typedef struct ih_core_test_server_context_t ih_core_test_server_context_t;

int main(int argc, char *argv[])
{
  ih_config_disable_if_running_batch_tests(argc, argv);

  ih_core_test_server_context_t custom_server_context;

  ih_net_server_system_t *server;
  unsigned short port;
  ih_net_engine_iengine_t iengine;
  ih_core_imessage_t messagey;
  ih_net_post_ipost_t ipost;

  ih_net_server_system_t *http_server;
  unsigned short http_port;
  ih_net_engine_iengine_t http_iengine;
  ih_core_imessage_t http_messagey;
  ih_net_post_ipost_t http_ipost;

  ih_core_log_t *log;

  log = ih_core_log_create(stdout);
  if (!log) {
    ih_core_trace_exit("x_audit_log_create");
  }

  port = 4545;

  ih_net_engine_iengine_init(&iengine, ih_net_test_engine_create,
      ih_net_test_engine_destroy, ih_net_test_engine_get_handler_for_message,
      ih_net_test_engine_maintain, ih_net_test_engine_run,
      ih_net_test_engine_start, ih_net_test_engine_stop);

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
      ih_net_post_system_is_socket_closed, ih_net_post_system_mod,
      ih_net_post_system_compare_equal);

  server = ih_net_server_system_create("standard", port, port,
      TEST_SERVER_MAX_THREADS, &messagey, &ipost,
      IH_NET_SERVER_SYSTEM_NO_CONFIG_SYSTEM, log);
  assert(server);

  if (!ih_net_server_system_register_engine(server, IH_CORE_ENGINE_TEST,
          &custom_server_context, &iengine, 2, 2, IH_NET_MAINTAIN_CONSTANTLY,
          IH_NET_TEST_MESSAGE_TYPE_COUNT)) {
    ih_core_trace_exit("x_net_server_register_engine");
  }

  http_port = 5454;

  ih_net_engine_iengine_init(&http_iengine, ih_net_test_http_engine_create,
      ih_net_test_http_engine_destroy,
      ih_net_test_http_engine_get_handler_for_message,
      ih_net_test_http_engine_maintain, ih_net_test_http_engine_run,
      ih_net_test_http_engine_start, ih_net_test_http_engine_stop);

  ih_core_imessage_init(&http_messagey, ih_net_http_message_destroy,
      ih_net_http_message_get_client_socket, ih_net_http_message_get_engine_id,
      ih_net_http_message_get_type);

  ih_net_post_ipost_init(&http_ipost, ih_net_http_post_compare,
      ih_net_http_post_create, ih_net_http_post_create_decoy,
      ih_net_http_post_destroy, ih_net_http_post_destroy_decoy,
      ih_net_http_post_get_last_receive_activity_time,
      ih_net_http_post_get_socket, ih_net_http_post_get_stats,
      ih_net_http_post_receive_message, ih_net_http_post_receive_messages,
      ih_net_http_post_send_message, ih_net_http_post_send_messages,
      ih_net_http_post_is_socket_closed, ih_net_http_post_mod,
      ih_net_http_post_compare_equal);

  http_server = ih_net_server_system_create("http", http_port, http_port,
      TEST_HTTP_SERVER_MAX_THREADS, &http_messagey, &http_ipost,
      IH_NET_SERVER_SYSTEM_NO_CONFIG_SYSTEM, log);
  assert(http_server);

  if (!ih_net_server_system_start(server)) {
    ih_core_trace_exit("x_net_server_start");
  }

  if (!ih_net_server_system_start(http_server)) {
    ih_core_trace_exit("x_net_server_start");
  }

  ih_net_server_system_destroy(server);
  ih_net_server_system_destroy(http_server);
  ih_core_log_destroy(log);

  return 0;
}
