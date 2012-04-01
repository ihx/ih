#include "ih/core/content.h"
#include "ih/core/tools.h"
#include "ih/net/engine/thread.h"
#include "ih/net/http/message.h"
#include "ih/net/server/system.h"
#include "ih/net/test/message.h"
#include "ih/net/test/http/engine.h"

struct ih_net_test_http_engine_t {
  void *things_the_engine_needs_to_share;
  ih_net_server_system_t *ih_net_server;
  void *custom_server_object;
};

static ih_net_message_status_t handle_about(void *engine_object,
    void *message_object);

static ih_net_message_status_t handle_not_found(void *engine_object,
    void *message_object);

ih_net_message_status_t handle_about(void *engine_object,
    void *message_object)
{
  assert(engine_object);
  assert(message_object);
  ih_net_test_http_engine_t *engine;
  ih_net_http_message_t *message;
  ih_net_http_message_t *response_message;
  int client_socket;
  ih_net_server_system_t *ih_net_server;
  char *body;
  unsigned long body_size;

  engine = engine_object;
  ih_net_server = engine->ih_net_server;
  message = message_object;
  client_socket = ih_core_message_get_client_socket(message);
  body = "about this site";
  body_size = strlen(body);

  response_message = ih_net_http_message_create(client_socket,
      IH_NET_HTTP_METHOD_UNKNOWN, IH_NET_HTTP_STATUS_OK,
      IH_NET_HTTP_MESSAGE_NO_RESOURCE_PATH, IH_NET_HTTP_VERSION_1_0,
      IH_NET_HTTP_MESSAGE_NO_HEADERS);
  if (response_message) {
    ih_net_http_message_set_body(response_message,
        IH_CORE_CONTENT_MIME_TEIH_HTML, body, body_size);
  } else {
    ih_core_trace("x_net_http_message_create");
  }

  if (!ih_net_server_system_send_message(ih_net_server, response_message)) {
    ih_core_trace("x_net_server_send_message");
  }

  return IH_NET_MESSAGE_STATUS_HANDLED;
}

ih_net_message_status_t handle_not_found(void *engine_object,
    void *message_object)
{
  assert(engine_object);
  assert(message_object);
  ih_net_test_http_engine_t *engine;
  ih_net_http_message_t *message;
  ih_net_http_message_t *response_message;
  int client_socket;
  ih_net_server_system_t *ih_net_server;
  char *body;
  unsigned long body_size;

  engine = engine_object;
  ih_net_server = engine->ih_net_server;
  message = message_object;
  client_socket = ih_core_message_get_client_socket(message);
  body = "test_http_engine cannot handle this request";
  body_size = strlen(body);

  response_message = ih_net_http_message_create(client_socket,
      IH_NET_HTTP_METHOD_UNKNOWN, IH_NET_HTTP_STATUS_NOT_FOUND,
      IH_NET_HTTP_MESSAGE_NO_RESOURCE_PATH, IH_NET_HTTP_VERSION_1_0,
      IH_NET_HTTP_MESSAGE_NO_HEADERS);
  if (response_message) {
    ih_net_http_message_set_body(response_message,
        IH_CORE_CONTENT_MIME_TEIH_HTML, body, body_size);
  } else {
    ih_core_trace("x_net_http_message_create");
  }

  if (!ih_net_server_system_send_message(ih_net_server, response_message)) {
    ih_core_trace("x_net_server_send_message");
  }

  return IH_NET_MESSAGE_STATUS_HANDLED;
}

void *ih_net_test_http_engine_create(ih_net_server_system_t *ih_net_server,
    void *custom_server_object)
{
  assert(ih_net_server);
  assert(custom_server_object);
  ih_net_test_http_engine_t *engine;

  printf("test_http_engine creating\n");

  engine = malloc(sizeof *engine);
  if (engine) {
    engine->ih_net_server = ih_net_server;
    engine->custom_server_object = custom_server_object;
  }

  return engine;
}

void ih_net_test_http_engine_destroy(void *engine_object)
{
  assert(engine_object);

  printf("test_http_engine destroying\n");
  free(engine_object);
}

ih_net_server_system_handle_message_f ih_net_test_http_engine_get_handler_for_message
(void *engine_object, void *_http_message_object)
{
  assert(engine_object);
  assert(_http_message_object);
  /*  ih_net_test_http_engine_t *engine;  */
  ih_net_server_system_handle_message_f handler;
  ih_net_http_message_t *_http_message;
  char *resource_name;

  /*  engine = engine_object;  */
  _http_message = _http_message_object;

  resource_name = ih_net_http_message_get_resource_name(_http_message);

  if (0 == strcmp("/", resource_name)) {
    handler = handle_about;

  } else if (0 == strcmp("/about", resource_name)) {
    handler = handle_about;

  } else {
    handler = handle_not_found;

  }

  return handler;
}

void ih_net_test_http_engine_maintain(void *engine_object)
{
  assert(engine_object);
  /*  ih_net_test_http_engine_t *engine;  */

  /*  engine = engine_object;  */
}

void ih_net_test_http_engine_run(void *engine_thread_object)
{
  assert(engine_thread_object);
  ih_net_engine_thread_t *engine_thread;
  ih_net_test_http_engine_t *engine;
  ih_net_server_system_t *ih_net_server;
  unsigned short thread_index;

  engine_thread = engine_thread_object;
  engine = engine_thread->engine_object;
  ih_net_server = engine->ih_net_server;
  thread_index = engine_thread->thread_index;

  ih_net_server_system_process_messages
    (ih_net_server, IH_CORE_ENGINE_HTTP, thread_index);
}

void ih_net_test_http_engine_start(void *engine_thread_object)
{
  assert(engine_thread_object);
  /*  ih_net_engine_thread_t *engine_thread;  */
  /*  ih_net_test_http_engine_t *engine;  */

  /*  engine_thread = engine_thread_object;  */
  /*  engine = engine_thread->engine_object;  */

  printf("test_http_engine starting\n");
}

void ih_net_test_http_engine_stop(void *engine_thread_object)
{
  assert(engine_thread_object);
  /*  ih_net_engine_thread_t *engine_thread;  */
  /*  ih_net_test_http_engine_t *engine;  */

  /*  engine_thread = engine_thread_object;  */
  /*  engine = engine_thread->engine_object;  */

  printf("test_http_engine stopping\n");
}
