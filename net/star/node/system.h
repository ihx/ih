#ifndef ih_net_star_node_system_h
#define ih_net_star_node_system_h

#include "ih/core/message.h"
#include "ih/net/server/system.h"
#include "ih/net/star/client/system.h"

struct ih_net_star_node_system_t;
typedef struct ih_net_star_node_system_t ih_net_star_node_system_t;

ih_net_star_node_system_t *ih_net_star_node_system_create
(char *node_ip, unsigned short node_min_port, unsigned short node_max_port,
    unsigned short node_max_threads, ih_case_list_t *peer_node_ips,
    unsigned short peer_node_port_min, unsigned short peer_node_port_max,
    ih_core_log_t *log);

void ih_net_star_node_system_destroy(ih_net_star_node_system_t *node);

ih_net_server_system_t *ih_net_star_node_system_get_server
(ih_net_star_node_system_t *node);

void ih_net_star_node_system_get_server_stats
(ih_net_star_node_system_t *node, ih_net_server_stats_t *server_stats);

ih_net_star_client_system_t *ih_net_star_node_system_get_starclient
(ih_net_star_node_system_t *node);

ih_core_bool_t ih_net_star_node_system_register_engine
(ih_net_star_node_system_t *node, ih_core_engine_id_t engine_id,
    void *custom_server_context, ih_net_engine_iengine_t *iengine,
    unsigned short min_run_threads, unsigned short max_run_threads,
    ih_net_maintain_t maintain_schedule, unsigned long message_type_count);

void ih_net_star_node_system_register_message_handler
(ih_net_star_node_system_t *node, ih_core_engine_id_t engine_id,
    unsigned long message_type,
    ih_net_server_system_handle_message_f message_handler);

ih_core_bool_t ih_net_star_node_system_send_message_to_all_peers
(ih_net_star_node_system_t *node, ih_core_message_t *message);

ih_core_bool_t ih_net_star_node_system_send_message_to_any_peer
(ih_net_star_node_system_t *node, ih_core_message_t *message);

ih_core_bool_t ih_net_star_node_system_send_message_to_client
(ih_net_star_node_system_t *node, ih_core_message_t *message);

void ih_net_star_node_system_set_server_unresponsive_client_time_seconds
(ih_net_star_node_system_t *node,
    unsigned long unresponsive_client_time_seconds);

ih_core_bool_t ih_net_star_node_system_start(ih_net_star_node_system_t *node);

#endif
