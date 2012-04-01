#ifndef ih_net_server_system_h
#define ih_net_server_system_h

#include "ih/case/list.h"
#include "ih/config/system.h"
#include "ih/core/engine.h"
#include "ih/core/imessage.h"
#include "ih/core/log.h"
#include "ih/core/message.h"
#include "ih/net/engine/iengine.h"
#include "ih/net/ip_address.h"
#include "ih/net/post/ipost.h"
#include "ih/net/server/stats.h"

#define IH_NET_SERVER_SYSTEM_MAX_ENGINES 64
#define IH_NET_SERVER_SYSTEM_NO_MAINTAIN_FUNCTION NULL
#define IH_NET_SERVER_SYSTEM_NO_CONFIG_SYSTEM NULL
#define IH_NET_SERVER_SYSTEM_DONT_CLOSE_UNRESPONSIVE_CLIENTS 0
#define IH_NET_MESSAGE_TYPE_COUNT_NONE 0

ih_net_server_system_t *ih_net_server_system_create(const char *name,
    unsigned short min_port, unsigned short max_port,
    unsigned short max_threads, ih_core_imessage_t *messagey,
    ih_net_post_ipost_t *ipost, ih_config_system_t *config_system,
    ih_core_log_t *log);

void ih_net_server_system_destroy(ih_net_server_system_t *server);

ih_core_bool_t ih_net_server_system_engine_run_thread_quiesce_requested
(ih_net_server_system_t *server, ih_core_engine_id_t engine_id,
    unsigned short thread_index);

ih_net_server_system_handle_message_f
ih_net_server_system_get_handler_for_message(ih_net_server_system_t *server,
    void *message_object);

ih_config_system_t *ih_net_server_system_get_config_system
(ih_net_server_system_t *server);

void ih_net_server_system_get_stats(ih_net_server_system_t *server,
    ih_net_server_stats_t *server_stats);

void ih_net_server_system_print_stats(ih_net_server_system_t *server);

void ih_net_server_system_process_messages(ih_net_server_system_t *server,
    ih_core_engine_id_t engine_id, unsigned short thread_index);

ih_core_bool_t ih_net_server_system_register_engine
(ih_net_server_system_t *server, ih_core_engine_id_t engine_id,
    void *custom_server_context, ih_net_engine_iengine_t *iengine,
    unsigned short min_run_threads, unsigned short max_run_threads,
    ih_net_maintain_t maintain_schedule, unsigned long message_type_count);

void ih_net_server_system_register_message_handler
(ih_net_server_system_t *server, ih_core_engine_id_t engine_id,
    unsigned long message_type,
    ih_net_server_system_handle_message_f message_handler);

ih_core_bool_t ih_net_server_system_send_message
(ih_net_server_system_t *server, void *message_object);

void ih_net_server_system_set_unresponsive_client_time_seconds
(ih_net_server_system_t *server,
    unsigned long unresponsive_client_time_seconds);

ih_core_bool_t ih_net_server_system_start(ih_net_server_system_t *server);

ih_case_list_t *ih_net_server_system_take_unprocessed_messages
(ih_net_server_system_t *server);

ih_case_list_t *ih_net_server_system_take_unsent_messages
(ih_net_server_system_t *server);

#endif
