#ifndef ih_net_post_system_h
#define ih_net_post_system_h

#include "ih/case/list.h"
#include "ih/core/message.h"
#include "ih/net/post/stats.h"

struct ih_net_post_system_t;
typedef struct ih_net_post_system_t ih_net_post_system_t;

int ih_net_post_system_compare(void *post_object_a, void *post_object_b);

ih_core_bool_t ih_net_post_system_compare_equal(void *post_object_a,
    void *post_object_b);

void *ih_net_post_system_create(int socket);

void *ih_net_post_system_create_decoy(int socket);

void ih_net_post_system_destroy(void *post_object);

void ih_net_post_system_destroy_decoy(void *post_object);

time_t ih_net_post_system_get_last_receive_activity_time(void *post_object);

int ih_net_post_system_get_socket(void *post_object);

void ih_net_post_system_get_stats(void *post_object,
    ih_net_post_stats_t *post_stats);

ih_core_bool_t ih_net_post_system_is_socket_closed(void *post_object);

unsigned long ih_net_post_system_mod(void *post_object, unsigned long divisor);

void *ih_net_post_system_receive_message(void *post_object);

void ih_net_post_system_receive_messages(void *post_object);

ih_core_bool_t ih_net_post_system_send_message(void *post_object,
    void *message_object);

void ih_net_post_system_send_messages(void *post_object);

ih_case_list_t *ih_net_post_system_take_unsent_messages
(ih_net_post_system_t *post);

#endif
