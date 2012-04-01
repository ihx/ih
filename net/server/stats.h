#ifndef ih_net_server_stats_h
#define ih_net_server_stats_h

#include "ih/core/message.h"

struct ih_net_server_stats_t {
  unsigned long engine_count;
  unsigned long server_send_message_failure_count;
  unsigned long engine_cant_handle_message_now_count;
  unsigned long engine_handled_message_count;
  unsigned long engine_cant_handle_message_count;
  unsigned long discarded_message_for_nonexistent_client_count;
  unsigned long discarded_message_for_unregistered_engine_count;
  unsigned long discarded_message_engine_inbox_add_failed_count;
  unsigned long uptime_seconds;
  unsigned long connected_client_count;
  unsigned short max_threads;
  unsigned short thread_count;
};
typedef struct ih_net_server_stats_t ih_net_server_stats_t;

ih_core_bool_t ih_net_server_system_add_stats_to_message
(ih_net_server_stats_t *server_stats, ih_core_message_t *message);

ih_net_server_stats_t *ih_net_server_system_create_stats_from_message
(ih_core_message_t *message);

void ih_net_server_stats_init(ih_net_server_stats_t *server_stats);

#endif
