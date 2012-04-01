#ifndef ih_net_star_client_system_h
#define ih_net_star_client_system_h

#include "ih/core/log.h"
#include "ih/core/engine.h"
#include "ih/net/client/system.h"
#include "ih/net/star/client/stats.h"

struct ih_net_star_client_system_t;
typedef struct ih_net_star_client_system_t ih_net_star_client_system_t;

ih_core_bool_t ih_net_star_client_system_connect
(ih_net_star_client_system_t *starclient);

ih_net_star_client_system_t *ih_net_star_client_system_create
(ih_case_list_t *star_arm_ips, unsigned short star_arm_port_min,
    unsigned short star_arm_port_max, char *node_server_exclude_ip,
    unsigned short node_server_exclude_min_port,
    unsigned short node_server_exclude_max_port, void *custom_client_context,
    ih_core_log_t *log);

void ih_net_star_client_system_destroy
(ih_net_star_client_system_t *starclient);

ih_net_client_system_t *ih_net_star_client_system_get_client
(ih_net_star_client_system_t *starclient, int socket);

void ih_net_star_client_system_get_stats
(ih_net_star_client_system_t *starclient,
    ih_net_star_client_stats_t *starclient_stats);

void ih_net_star_client_system_process_messages
(ih_net_star_client_system_t *starclient);

ih_core_bool_t ih_net_star_client_system_register_engine
(ih_net_star_client_system_t *starclient, ih_core_engine_id_t engine_id,
    unsigned long message_type_count);

void ih_net_star_client_system_register_message_handler
(ih_net_star_client_system_t *starclient, ih_core_engine_id_t engine_id,
    unsigned long message_type,
    ih_net_client_system_handle_message_f message_handler);

ih_core_bool_t ih_net_star_client_system_send_message_to_any_arm
(ih_net_star_client_system_t *starclient, ih_core_message_t *message);

ih_core_bool_t ih_net_star_client_system_send_message_to_all_arms
(ih_net_star_client_system_t *starclient, ih_core_message_t *message);

void ih_net_star_client_system_set_unsent_messages_queue_size
(ih_net_star_client_system_t *starclient, unsigned long queue_size);

ih_core_bool_t ih_net_star_client_system_star_available
(ih_net_star_client_system_t *starclient);

#endif
