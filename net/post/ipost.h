#ifndef ih_net_post_ipost_h
#define ih_net_post_ipost_h

#include "ih/core/object.h"
#include "ih/core/standard.h"
#include "ih/net/post/stats.h"

typedef int (*ih_net_post_ipost_compare_f)(void *a_object, void *b_object);

typedef void *(*ih_net_post_ipost_create_f)(int socket);

typedef void *(*ih_net_post_ipost_create_decoy_f)(int socket);

typedef void (*ih_net_post_ipost_destroy_f)(void *post_object);

typedef void (*ih_net_post_ipost_destroy_decoy_f)(void *post_object);

typedef time_t (*ih_net_post_ipost_get_last_receive_activity_time_f)
(void *post_object);

typedef int (*ih_net_post_ipost_get_socket_f)(void *post_object);

typedef void (*ih_net_post_ipost_get_stats_f)(void *post_object,
    ih_net_post_stats_t *post_stats);

typedef void *(*ih_net_post_ipost_receive_message_f)(void *post_object);

typedef void (*ih_net_post_ipost_receive_messages_f)(void *post_object);

typedef ih_core_bool_t (*ih_net_post_ipost_send_message_f)(void *post_object,
    void *message_object);

typedef void (*ih_net_post_ipost_send_messages_f)(void *post_object);

typedef ih_core_bool_t (*ih_net_post_ipost_socket_closed_f)(void *post_object);

struct ih_net_post_ipost_t {
  ih_net_post_ipost_compare_f compare;
  ih_net_post_ipost_create_f create;
  ih_net_post_ipost_create_decoy_f create_decoy;
  ih_net_post_ipost_destroy_f destroy;
  ih_net_post_ipost_destroy_decoy_f destroy_decoy;

  ih_net_post_ipost_get_last_receive_activity_time_f
  get_last_receive_activity_time;

  ih_net_post_ipost_get_socket_f get_socket;
  ih_net_post_ipost_get_stats_f get_stats;
  ih_net_post_ipost_receive_message_f receive_message;
  ih_net_post_ipost_receive_messages_f receive_messages;
  ih_net_post_ipost_send_message_f send_message;
  ih_net_post_ipost_send_messages_f send_messages;
  ih_net_post_ipost_socket_closed_f socket_closed;

  ih_core_object_hash_f hash;
  ih_core_object_compare_equal_f compare_equal;
};
typedef struct ih_net_post_ipost_t ih_net_post_ipost_t;

void ih_net_post_ipost_init(ih_net_post_ipost_t *ipost,
    ih_net_post_ipost_compare_f compare, ih_net_post_ipost_create_f create,
    ih_net_post_ipost_create_decoy_f create_decoy,
    ih_net_post_ipost_destroy_f destroy,
    ih_net_post_ipost_destroy_decoy_f destroy_decoy,

    ih_net_post_ipost_get_last_receive_activity_time_f
    get_last_receive_activity_time,

    ih_net_post_ipost_get_socket_f get_socket,
    ih_net_post_ipost_get_stats_f get_stats,
    ih_net_post_ipost_receive_message_f receive_message,
    ih_net_post_ipost_receive_messages_f receive_messages,
    ih_net_post_ipost_send_message_f send_message,
    ih_net_post_ipost_send_messages_f send_messages,
    ih_net_post_ipost_socket_closed_f socket_closed,

    ih_core_object_hash_f hash,
    ih_core_object_compare_equal_f compare_equal);

#endif
