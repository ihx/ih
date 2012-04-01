#include "ih/core/object.h"
#include "ih/core/tools.h"
#include "ih/net/engine/thread.h"
#include "ih/net/server/system.h"
#include "ih/seq/engine.h"
#include "ih/seq/message.h"

struct ih_seq_engine_t {
  void *things_the_engine_needs_to_share;
  ih_net_server_system_t *ih_net_server;
  void *custom_server_object;
};

static ih_net_message_status_t handle_get_last_n(void *engine_object,
    void *message_object)
{
  return IH_NET_MESSAGE_STATUS_CANT_HANDLE;
}

static ih_net_message_status_t handle_get_since_timestamp(void *engine_object,
    void *message_object)
{
  return IH_NET_MESSAGE_STATUS_CANT_HANDLE;
}

ih_net_message_status_t handle_ping(void *engine_object,
    void *message_object)
{
  /*
  assert(engine_object);
  assert(message_object);
  ih_seq_ping_t *ping;
  ih_seq_pong_t *pong;
  ih_core_message_t *pong_message;
  ih_seq_engine_t *engine;
  ih_net_server_system_t *ih_net_server;
  ih_net_message_status_t message_status;
  int client_socket;
  ih_core_message_t *message;
  char *ping_string;

  message = message_object;
  engine = engine_object;
  ih_net_server = engine->ih_net_server;
  client_socket = ih_core_message_get_client_socket(message);

  ping = ih_seq_ping_create_from_message(message);
  if (ping) {
    ping_string = ih_seq_ping_get_string(ping);
    if (ping_string) {
      pong = ih_seq_pong_create(ping_string);
      if (pong) {
        pong_message = ih_seq_message_create
          (client_socket, IH_SEQ_MESSAGE_PONG);
        if (pong_message) {
          if (ih_seq_pong_add_to_message(pong, pong_message)) {
            if (ih_net_server_system_send_message(ih_net_server, pong_message)) {
              message_status = IH_NET_MESSAGE_STATUS_HANDLED;
            } else {
              ih_core_trace("x_net_server_send_message() failed");
              message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
              ih_core_message_destroy(pong_message);
            }
          } else {
            ih_core_trace("x_seq_pong_add_to_message");
            message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
            ih_core_message_destroy(pong_message);
          }
        } else {
          ih_core_trace("x_seq_message_create");
          message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
        }
        ih_seq_pong_destroy(pong);
      } else {
        ih_core_trace("x_seq_pong_create");
        message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
      }
      ih_seq_ping_destroy(ping);
    } else {
      ih_core_trace("x_seq_ping_get_string");
      message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
    }
  } else {
    ih_core_trace("x_seq_ping_create");
    message_status = IH_NET_MESSAGE_STATUS_CANT_HANDLE;
  }

  return message_status;
  */
  return IH_NET_MESSAGE_STATUS_CANT_HANDLE;
}

void *ih_seq_engine_create(ih_net_server_system_t *ih_net_server,
    void *custom_server_object)
{
  assert(ih_net_server);
  assert(custom_server_object);
  ih_seq_engine_t *engine;

  engine = malloc(sizeof *engine);
  if (engine) {
    engine->ih_net_server = ih_net_server;
    engine->custom_server_object = custom_server_object;
  }

  ih_net_server_system_register_message_handler(ih_net_server,
      IH_CORE_ENGINE_SEQ, IH_SEQ_MESSAGE_REQUEST_GET_LAST_N,
      handle_get_last_n);
  ih_net_server_system_register_message_handler(ih_net_server,
      IH_CORE_ENGINE_SEQ, IH_SEQ_MESSAGE_REQUEST_GET_SINCE_TIMESTAMP,
      handle_get_since_timestamp);

  return engine;
}

void ih_seq_engine_destroy(void *engine_object)
{
  free(engine_object);
}

ih_net_server_system_handle_message_f ih_seq_engine_get_handler_for_message
(void *engine_object, void *message_object)
{
  assert(engine_object);
  assert(message_object);
  ih_seq_engine_t *engine;
  ih_net_server_system_handle_message_f handler;
  ih_core_message_t *message;

  engine = engine_object;
  message = message_object;
  handler = ih_net_server_system_get_handler_for_message
    (engine->ih_net_server, message);

  return handler;
}

void ih_seq_engine_maintain(void *engine_object)
{
  assert(engine_object);
  ih_seq_engine_t *engine;
  ih_net_server_system_t *ih_net_server;

  engine = engine_object;
  ih_net_server = engine->ih_net_server;

  ih_net_server_system_print_stats(ih_net_server);
}

void ih_seq_engine_run(void *engine_thread_object)
{
  assert(engine_thread_object);
  ih_net_engine_thread_t *engine_thread;
  ih_seq_engine_t *engine;
  ih_net_server_system_t *ih_net_server;
  unsigned char thread_index;

  engine_thread = engine_thread_object;
  engine = engine_thread->engine_object;
  ih_net_server = engine->ih_net_server;
  thread_index = engine_thread->thread_index;

  ih_net_server_system_process_messages(ih_net_server, IH_CORE_ENGINE_SEQ,
      thread_index);
}

void ih_seq_engine_start(void *engine_thread_object)
{
  assert(engine_thread_object);
  /*  ih_net_engine_thread_t *engine_thread;  */
  /*  ih_seq_engine_t *engine;  */

  /*  engine_thread = engine_thread_object;  */
  /*  engine = engine_thread->engine_object;  */

  printf("[ping] ping engine starting\n");
}

void ih_seq_engine_stop(void *engine_thread_object)
{
  assert(engine_thread_object);
  /*  ih_net_engine_thread_t *engine_thread;  */
  /*  ih_seq_engine_t *engine;  */

  /*  engine_thread = engine_thread_object;  */
  /*  engine = engine_thread->engine_object;  */

  printf("[ping] ping engine stopping\n");
}
