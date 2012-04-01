#ifndef ih_net_client_system_h
#define ih_net_client_system_h

#include "ih/core/log.h"
#include "ih/case/list.h"
#include "ih/core/message.h"
#include "ih/core/imessage.h"
#include "ih/net/post/ipost.h"

struct ih_net_client_system_t;
typedef struct ih_net_client_system_t ih_net_client_system_t;

typedef void (*ih_net_client_system_handle_message_f)
(void *custom_client_context, ih_core_message_t *message);

void *ih_net_client_system_copy(void *client_object);

ih_net_client_system_t *ih_net_client_system_create
(const char *server_ip_address, unsigned short server_min_port,
    unsigned short server_max_port, void *custom_client_context,
    ih_core_log_t *log);

void ih_net_client_system_destroy(void *client_object);

char *ih_net_client_system_get_as_string(void *client_object);

char *ih_net_client_system_get_server_ip_address
(ih_net_client_system_t *client);

unsigned short ih_net_client_system_get_server_port
(ih_net_client_system_t *client);

int ih_net_client_system_get_socket(ih_net_client_system_t *client);

ih_core_bool_t ih_net_client_system_is_connected_to_server
(ih_net_client_system_t *client);

void ih_net_client_system_print(void *client_object);

void ih_net_client_system_process_messages(ih_net_client_system_t *client);

ih_core_bool_t ih_net_client_system_register_engine
(ih_net_client_system_t *client, ih_core_engine_id_t engine_id,
    unsigned long message_type_count);

void ih_net_client_system_register_message_handler
(ih_net_client_system_t *client, ih_core_engine_id_t engine_id,
    unsigned long message_type,
    ih_net_client_system_handle_message_f message_handler);

ih_core_bool_t ih_net_client_system_send_message
(ih_net_client_system_t *client, ih_core_message_t *message);

ih_case_list_t *ih_net_client_system_take_unsent_messages
(ih_net_client_system_t *client);

#endif
