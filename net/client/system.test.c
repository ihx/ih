#include "ih/config/tools.h"
#include "ih/core/message.h"
#include "ih/core/tools.h"
#include "ih/net/client/system.h"
#include "ih/net/ping.h"
#include "ih/net/test/engine.h"
#include "ih/net/test/message.h"

#define IH_NET_CLIENT_SYSTEM_TEST_SLEEP_MICROSECONDS \
  IH_CORE_STANDARD_SLEEP_MICROSECONDS

struct test_client_context_t {
  ih_core_bool_t pong_received;
};
typedef struct test_client_context_t test_client_context_t;

static void handle_pong(void *custom_client_context,
    ih_core_message_t *message);

void handle_pong(void *custom_client_context, ih_core_message_t *message)
{
  assert(custom_client_context);
  assert(message);
  test_client_context_t *client_context;
  char *pong_string;

  client_context = custom_client_context;

  client_context->pong_received = ih_core_bool_true;
  pong_string = ih_core_message_take_string(message);
  printf("%s\n", pong_string);

  free(pong_string);
  assert(client_context->pong_received);
}

int main(int argc, char *argv[])
{
  ih_config_disable_if_running_batch_tests(argc, argv);

  ih_net_client_system_t *client;
  ih_core_message_t *ping_message;
  test_client_context_t test_client_context;
  ih_net_ping_t *ping;
  ih_core_log_t *log;

  test_client_context.pong_received = ih_core_bool_false;

  log = ih_core_log_create(stdout);
  if (!log) {
    ih_core_trace_exit("x_audit_log_create");
  }

  client = ih_net_client_system_create("127.0.0.1", 4545, 4545,
      &test_client_context, log);
  if (!client) {
    ih_core_trace_exit("x_net_client_create()");
  }
  ih_net_client_system_register_engine(client, IH_CORE_ENGINE_TEST,
      IH_NET_TEST_MESSAGE_TYPE_COUNT);
  ih_net_client_system_register_message_handler(client, IH_CORE_ENGINE_TEST,
      IH_NET_TEST_MESSAGE_PONG, handle_pong);

  ping = ih_net_ping_create("penta");
  if (!ping) {
    ih_core_trace_exit("x_net_ping_create");
  }

  ping_message = ih_net_test_message_create
    (IH_CORE_IMESSAGE_NO_CLIENT_SOCKET, IH_NET_TEST_MESSAGE_PING);
  if (!ping_message) {
    ih_core_trace_exit("x_net_testmessage_create");
  }

  if (!ih_net_ping_add_to_message(ping, ping_message)) {
    ih_core_trace_exit("x_net_ping_add_to_message");
  }

  ih_net_ping_destroy(ping);

  if (ih_net_client_system_send_message(client, ping_message)) {
    printf("client sent ping message\n");
  } else {
    ih_core_message_destroy(ping_message);
    ih_core_trace_exit("x_net_client_send_message");
  }

  do {
    ih_net_client_system_process_messages(client);
    usleep(IH_NET_CLIENT_SYSTEM_TEST_SLEEP_MICROSECONDS);
  } while (!test_client_context.pong_received);

  ih_net_client_system_destroy(client);
  ih_core_log_destroy(log);

  return 0;
}
