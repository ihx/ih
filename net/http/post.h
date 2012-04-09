#ifndef ih_net_http_post_h
#define ih_net_http_post_h

#include "ih/core/object.h"
#include "ih/net/post/stats.h"

struct ih_net_http_post_t;
typedef struct ih_net_http_post_t ih_net_http_post_t;

int ih_net_http_post_compare(void *http_post_object_a,
    void *http_post_object_b);

ih_core_bool_t ih_net_http_post_compare_equal(void *http_post_object_a,
    void *http_post_object_b);

void *ih_net_http_post_create(int socket);

void *ih_net_http_post_create_decoy(int socket);

void ih_net_http_post_destroy(void *http_post_object);

void ih_net_http_post_destroy_decoy(void *http_post_object);

time_t ih_net_http_post_get_last_receive_activity_time(void *http_post_object);

int ih_net_http_post_get_socket(void *http_post_object);

void ih_net_http_post_get_stats(void *http_post_object,
    ih_net_post_stats_t *post_stats);

unsigned long ih_net_http_post_hash(void *post_object);

ih_core_bool_t ih_net_http_post_is_socket_closed(void *http_post_object);

void *ih_net_http_post_receive_message(void *http_post_object);

void ih_net_http_post_receive_messages(void *http_post_object);

ih_core_bool_t ih_net_http_post_send_message(void *http_post_object,
    void *http_message_object);

void ih_net_http_post_send_messages(void *http_post_object);

#endif
