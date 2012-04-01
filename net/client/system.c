#include "ih/core/tools.h"
#include "ih/net/client/system.h"
#include "ih/net/client/socket.h"
#include "ih/net/exchange.h"
#include "ih/net/post/system.h"
#include "ih/net/post/ipost.h"

struct engine_container_t {
  ih_core_engine_id_t engine_id;
  ih_net_client_system_handle_message_f *message_handlers;
  unsigned long message_handlers_size;
};
typedef struct engine_container_t engine_container_t;

struct ih_net_client_system_t {
  int socket;

  ih_net_post_system_t *post;
  ih_net_exchange_t *exchange;
  pthread_mutex_t messaging_mutex;

  void *custom_client_context;
  char *server_ip_address;
  unsigned short server_min_port;
  unsigned short server_max_port;
  unsigned short server_port;

  ih_case_list_t *engines;
  engine_container_t *engines_array[IH_CORE_ENGINE_TYPE_COUNT];

  ih_core_bool_t server_socket_closed;

  ih_net_post_ipost_t ipost;

  ih_core_log_t *log;
};

static ih_core_bool_t connect_to_server(ih_net_client_system_t *client);

static void destroy_engine_container(void *object);

static ih_core_bool_t ensure_client_is_connected
(ih_net_client_system_t *client);

static ih_core_bool_t handle_disconnect(ih_net_client_system_t *client);

static ih_core_message_t *receive_message(ih_net_client_system_t *client);

ih_core_bool_t connect_to_server(ih_net_client_system_t *client)
{
  assert(client);
  ih_core_bool_t success;
  unsigned short port;

  success = ih_core_bool_false;

  for (port = client->server_min_port;
       (port <= client->server_max_port) && (!success); port++) {
    client->socket
      = ih_net_client_socket_create(client->server_ip_address, port);
    if (client->socket >= 0) {
      client->server_socket_closed = ih_core_bool_false;
      client->server_port = port;

      ih_core_log_enter(client->log, "xnet",
          "client connected to server on port %i", port);

      pthread_mutex_lock(&client->messaging_mutex);
      {
        client->post = ih_net_post_system_create(client->socket);
        if (client->post) {
          if (ih_net_exchange_register_post
              (client->exchange, client->post)) {
            success = ih_core_bool_true;
          } else {
            ih_core_log_trace(client->log, "xnet",
                "x_net_exchange_register_post");
            ih_net_client_socket_destroy(client->socket);
            client->server_socket_closed = ih_core_bool_true;
            ih_net_post_system_destroy(client->post);
            client->post = NULL;
          }
        } else {
          ih_core_log_trace(client->log, "xnet", "x_net_post_create");
          ih_net_client_socket_destroy(client->socket);
          client->server_socket_closed = ih_core_bool_true;
        }
      }
      pthread_mutex_unlock(&client->messaging_mutex);

    } else {
      ih_core_log_enter(client->log, "xnet",
          "client could not connect to server on port %i", port);
    }
  }

  return success;
}

void destroy_engine_container(void *object)
{
  assert(object);
  engine_container_t *engine_container;

  engine_container = object;
  free(engine_container->message_handlers);
  free(engine_container);
}

ih_core_bool_t ensure_client_is_connected(ih_net_client_system_t *client)
{
  assert(client);
  ih_core_bool_t connected;

  connected = ih_core_bool_true;

  if (client->server_socket_closed) {
    connected = connect_to_server(client);
    if (connected) {
      ih_core_log_enter(client->log, "xnet", "reconnected to server");
    } else {
      ih_core_log_enter(client->log, "xnet", "could not reconnect to server");
    }
  }

  return connected;
}

ih_core_bool_t handle_disconnect(ih_net_client_system_t *client)
{
  assert(client);
  ih_core_bool_t success;

  ih_core_log_enter(client->log, "xnet", "lost connection to server");

  if (ih_net_exchange_unregister_post(client->exchange, client->socket)) {
    success = ih_core_bool_true;
    ih_net_post_system_destroy(client->post);
    client->post = NULL;
  } else {
    success = ih_core_bool_false;
    ih_core_log_trace(client->log, "xnet", "x_net_exchange_unregister_post");
  }

  return success;
}

void *ih_net_client_system_copy(void *client_object)
{
  ih_core_trace_exit("TODO: implement");
  return NULL;
}

ih_net_client_system_t *ih_net_client_system_create
(const char *server_ip_address, unsigned short server_min_port,
    unsigned short server_max_port, void *custom_client_context,
    ih_core_log_t *log)
{
  assert(server_ip_address);
  ih_net_client_system_t *client;
  ih_core_bool_t success;
  unsigned long each_engine_id;
  ih_core_bool_t messaging_mutex_needs_destroy;
  ih_core_bool_t connected;

  messaging_mutex_needs_destroy = ih_core_bool_false;
  connected = ih_core_bool_false;

  client = malloc(sizeof *client);
  if (client) {
    client->log = log;
    client->post = NULL;
    client->custom_client_context = custom_client_context;
    client->server_min_port = server_min_port;
    client->server_max_port = server_max_port;
    client->server_socket_closed = ih_core_bool_true;
    for (each_engine_id = 0; each_engine_id < IH_CORE_ENGINE_TYPE_COUNT;
         each_engine_id++) {
      *(client->engines_array + each_engine_id) = NULL;
    }
    ih_net_post_ipost_init(&client->ipost, ih_net_post_system_compare,
        ih_net_post_system_create, ih_net_post_system_create_decoy,
        ih_net_post_system_destroy, ih_net_post_system_destroy_decoy,
        ih_net_post_system_get_last_receive_activity_time,
        ih_net_post_system_get_socket, ih_net_post_system_get_stats,
        ih_net_post_system_receive_message,
        ih_net_post_system_receive_messages, ih_net_post_system_send_message,
        ih_net_post_system_send_messages,
        ih_net_post_system_is_socket_closed, ih_net_post_system_mod,
        ih_net_post_system_compare_equal);
    success = ih_core_bool_true;
  } else {
    success = ih_core_bool_false;
    ih_core_log_trace(client->log, "xnet", "malloc");
  }

  if (success) {
    client->server_ip_address = strdup(server_ip_address);
    if (!client->server_ip_address) {
      success = ih_core_bool_false;
    }
  }

  if (success) {
    client->exchange = ih_net_exchange_create(&client->ipost);
    if (!client->exchange) {
      success = ih_core_bool_false;
    }
  }

  if (success) {
    client->engines = ih_case_list_create(IH_CORE_OBJECT_NO_COMPARE_F,
        IH_CORE_OBJECT_NO_COPY_F, destroy_engine_container);
    if (!client->engines) {
      success = ih_core_bool_false;
    }
  }

  if (success) {
    if (0 == pthread_mutex_init(&client->messaging_mutex, NULL)) {
      messaging_mutex_needs_destroy = ih_core_bool_true;
    } else {
      success = ih_core_bool_false;
      ih_core_log_trace(client->log, "xnet", "pthread_mutex_init");
    }
  }

  if (success) {
    connected = connect_to_server(client);
    if (!connected) {
      success = ih_core_bool_false;
      ih_core_log_trace(client->log, "xnet", "connect_to_server");
    }
  }

  if (!success && client) {
    if (connected) {
      ih_net_client_socket_destroy(client->socket);
    }
    if (client->exchange) {
      ih_net_exchange_destroy(client->exchange);
    }
    if (client->server_ip_address) {
      free(client->server_ip_address);
    }
    if (client->engines) {
      ih_case_list_destroy(client->engines);
    }
    if (messaging_mutex_needs_destroy) {
      pthread_mutex_destroy(&client->messaging_mutex);
    }
    free(client);
    client = NULL;
  }

  return client;
}

void ih_net_client_system_destroy(void *client_object)
{
  assert(client_object);
  ih_net_client_system_t *client;

  client = client_object;

  ih_net_client_socket_destroy(client->socket);
  if (client->post) {
    ih_net_post_system_destroy(client->post);
  }
  ih_net_exchange_destroy(client->exchange);
  free(client->server_ip_address);
  ih_case_list_destroy(client->engines);
  pthread_mutex_destroy(&client->messaging_mutex);

  free(client);
}

char *ih_net_client_system_get_as_string(void *client_object)
{
  ih_core_trace_exit("TODO: implement");
  return NULL;
}

char *ih_net_client_system_get_server_ip_address
(ih_net_client_system_t *client)
{
  return client->server_ip_address;
}

unsigned short ih_net_client_system_get_server_port
(ih_net_client_system_t *client)
{
  return client->server_port;
}

int ih_net_client_system_get_socket(ih_net_client_system_t *client)
{
  return client->socket;
}

ih_core_bool_t ih_net_client_system_is_connected_to_server
(ih_net_client_system_t *client)
{
  return !client->server_socket_closed;
}

void ih_net_client_system_print(void *client_object)
{
  ih_core_trace_exit("TODO: implement");
}

void ih_net_client_system_process_messages(ih_net_client_system_t *client)
{
  ih_core_message_t *message;
  unsigned long message_type;
  ih_net_client_system_handle_message_f handler;
  engine_container_t *engine_container;
  ih_core_engine_id_t engine_id;

  handler = NULL;

  if (ensure_client_is_connected(client)) {
    while ((message = receive_message(client))) {
      message_type = ih_core_message_get_type(message);
      engine_id = ih_core_message_get_engine_id(message);
      engine_container = *(client->engines_array + engine_id);
      if (message_type < engine_container->message_handlers_size) {
        handler = *(engine_container->message_handlers + message_type);
        if (handler) {
          (*handler)(client->custom_client_context, message);
        }
      }
      if (!handler) {
        printf("client has no handler for %s engine's message %lu\n",
            ih_core_engine_get_name(engine_container->engine_id),
            message_type);
      }
      ih_core_message_destroy(message);
    }
  } else {
    ih_core_log_trace(client->log, "xnet", "ensure_client_is_connected");
  }
}

ih_core_bool_t ih_net_client_system_register_engine
(ih_net_client_system_t *client, ih_core_engine_id_t engine_id,
    unsigned long message_type_count)
{
  engine_container_t *engine_container;
  ih_core_bool_t success;
  unsigned short each_handler;

  engine_container = malloc(sizeof *engine_container);
  if (engine_container) {
    engine_container->engine_id = engine_id;
    success = ih_core_bool_true;
  } else {
    ih_core_log_trace(client->log, "xnet", "malloc");
    success = ih_core_bool_false;
  }

  if (success) {
    engine_container->message_handlers_size = message_type_count;
    engine_container->message_handlers
      = malloc((sizeof *engine_container->message_handlers)
          * message_type_count);
    if (engine_container->message_handlers) {
      for (each_handler = 0; each_handler < message_type_count;
           each_handler++) {
        *(engine_container->message_handlers + each_handler) = NULL;
      }
      success = ih_core_bool_true;
    } else {
      ih_core_log_trace(client->log, "xnet", "malloc");
      success = ih_core_bool_false;
    }
  }

  if (success) {
    *(client->engines_array + engine_id) = engine_container;
    if (!ih_case_list_add_last(client->engines, engine_container)) {
      success = ih_core_bool_false;
    }
  }

  return success;
}

void ih_net_client_system_register_message_handler
(ih_net_client_system_t *client, ih_core_engine_id_t engine_id,
    unsigned long message_type,
    ih_net_client_system_handle_message_f message_handler)
{
  assert(client);
  assert(message_handler);
  assert(client->engines_array[engine_id]);
  assert(message_type
      < client->engines_array[engine_id]->message_handlers_size);
  engine_container_t *engine_container;

  engine_container = client->engines_array[engine_id];
  *(engine_container->message_handlers + message_type) = message_handler;
}

ih_core_bool_t ih_net_client_system_send_message
(ih_net_client_system_t *client, ih_core_message_t *message)
{
  ih_core_bool_t success;

  if (ensure_client_is_connected(client)) {

    pthread_mutex_lock(&client->messaging_mutex);
    {
      if (ih_net_post_system_send_message(client->post, message)) {
        success = ih_core_bool_true;
        ih_net_exchange_send_and_receive_messages(client->exchange);

        if (ih_net_post_system_is_socket_closed(client->post)) {
          client->server_socket_closed = ih_core_bool_true;
          if (!handle_disconnect(client)) {
            ih_core_log_trace(client->log, "xnet", "handle_disconnect");
          }
        }
      } else {
        success = ih_core_bool_false;
        ih_core_log_trace(client->log, "xnet", "x_net_post_send_message");
      }
    }
    pthread_mutex_unlock(&client->messaging_mutex);

  } else {
    success = ih_core_bool_false;
    ih_core_log_trace(client->log, "xnet", "ensure_client_is_connected");
  }

  return success;
}

ih_case_list_t *ih_net_client_system_take_unsent_messages
(ih_net_client_system_t *client)
{
  assert(client);
  ih_case_list_t *messages;

  pthread_mutex_lock(&client->messaging_mutex);
  messages = ih_net_post_system_take_unsent_messages(client->post);
  pthread_mutex_unlock(&client->messaging_mutex);

  return messages;
}

ih_core_message_t *receive_message(ih_net_client_system_t *client)
{
  ih_core_message_t *message;

  if (ensure_client_is_connected(client)) {

    pthread_mutex_lock(&client->messaging_mutex);
    {
      ih_net_exchange_send_and_receive_messages(client->exchange);
      message = ih_net_post_system_receive_message(client->post);

      if (ih_net_post_system_is_socket_closed(client->post)) {
        client->server_socket_closed = ih_core_bool_true;
        if (!handle_disconnect(client)) {
          ih_core_log_trace(client->log, "xnet", "handle_disconnect");
        }
      }
    }
    pthread_mutex_unlock(&client->messaging_mutex);

  } else {
    message = NULL;
    ih_core_log_trace(client->log, "xnet", "ensure_client_is_connected");
  }

  return message;
}
