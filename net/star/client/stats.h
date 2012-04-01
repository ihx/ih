#ifndef ih_net_star_client_stats_h
#define ih_net_star_client_stats_h

#include "ih/core/message.h"

struct ih_net_star_client_stats_t {
  unsigned long connected_server_count;
};
typedef struct ih_net_star_client_stats_t ih_net_star_client_stats_t;

ih_core_bool_t ih_net_star_client_system_add_stats_to_message
(ih_net_star_client_stats_t *starclient_stats, ih_core_message_t *message);

ih_net_star_client_stats_t *ih_net_star_client_system_create_stats_from_message
(ih_core_message_t *message);

#endif
