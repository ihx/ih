#include "ih/case/set.h"
#include "ih/core/tools.h"
#include "ih/net/exchange.h"

struct ih_net_exchange_t {
  ih_case_set_t *posts;
  ih_net_post_ipost_t *ipost;
  ih_core_iobject_t ipost_iobject;
};

ih_net_exchange_t *ih_net_exchange_create(ih_net_post_ipost_t *ipost)
{
  assert(ipost);
  ih_net_exchange_t *exchange;
  ih_core_bool_t success;

  exchange = malloc(sizeof *exchange);
  if (exchange) {
    success = ih_core_bool_true;
    exchange->ipost = ipost;
    ih_core_iobject_init(&exchange->ipost_iobject, ipost->compare,
        ipost->compare_equal, IH_CORE_OBJECT_NO_COPY_F,
        IH_CORE_OBJECT_NO_DESTROY_F, IH_CORE_OBJECT_NO_GET_AS_STRING_F,
        ipost->hash);
    exchange->posts = ih_case_set_create(&exchange->ipost_iobject);
    if (!exchange->posts) {
      ih_core_trace("x_case_set_create");
      success = ih_core_bool_false;
    }
  } else {
    ih_core_trace("malloc");
    success = ih_core_bool_false;
  }

  if (!success && exchange) {
    ih_case_set_destroy(exchange->posts);
    free(exchange);
    exchange = NULL;
  }

  return exchange;
}

void ih_net_exchange_destroy(ih_net_exchange_t *exchange)
{
  ih_case_set_destroy(exchange->posts);
  free(exchange);
}

unsigned long ih_net_exchange_get_post_count(ih_net_exchange_t *exchange)
{
  return ih_case_set_get_size(exchange->posts);
}

ih_core_bool_t ih_net_exchange_register_post(ih_net_exchange_t *exchange,
    void *post_object)
{
  return ih_case_set_add(exchange->posts, post_object);
}

void ih_net_exchange_send_and_receive_messages(ih_net_exchange_t *exchange)
{
  fd_set read_sockets;
  fd_set write_sockets;
  int max_socket;
  void *post_object;
  int socket;
  struct timeval select_timeout;

  FD_ZERO(&read_sockets);
  FD_ZERO(&write_sockets);
  max_socket = 0;
  select_timeout.tv_sec = 0;
  select_timeout.tv_usec = 0;

  ih_case_set_iterate_start(exchange->posts);
  while ((post_object = ih_case_set_iterate_next(exchange->posts))) {
    socket = exchange->ipost->get_socket(post_object);
    FD_SET(socket, &read_sockets);
    FD_SET(socket, &write_sockets);
    if (socket > max_socket) {
      max_socket = socket;
    }
  }

  if (select(max_socket + 1, &read_sockets, &write_sockets, NULL,
          &select_timeout) > 0) {
    ih_case_set_iterate_start(exchange->posts);
    while ((post_object = ih_case_set_iterate_next(exchange->posts))) {
      socket = exchange->ipost->get_socket(post_object);
      if (FD_ISSET(socket, &read_sockets)) {
        exchange->ipost->receive_messages(post_object);
      }
      if (FD_ISSET(socket, &write_sockets)) {
        exchange->ipost->send_messages(post_object);
      }
    }
  }
}

ih_core_bool_t ih_net_exchange_unregister_post(ih_net_exchange_t *exchange,
    int socket)
{
  void *decoy_post_object;
  ih_core_bool_t success;

  decoy_post_object = exchange->ipost->create_decoy(socket);
  if (decoy_post_object) {
    success = ih_core_bool_true;
    if (!ih_case_set_remove(exchange->posts, decoy_post_object)) {
      ih_core_do_nothing();
      ih_core_trace("x_case_set_remove");
      success = ih_core_bool_false;
    }
    exchange->ipost->destroy_decoy(decoy_post_object);
  } else {
    ih_core_trace("ipost->create_decoy");
    success = ih_core_bool_false;
  }

  return success;
}
