#ifndef ih_net_test_http_engine_h
#define ih_net_test_http_engine_h

#include "ih/core/engine.h"

struct ih_net_test_http_engine_t;
typedef struct ih_net_test_http_engine_t ih_net_test_http_engine_t;

void *ih_net_test_http_engine_create(ih_net_server_system_t *ih_net_server,
    void *custom_server_object);

ih_net_server_system_handle_message_f
ih_net_test_http_engine_get_handler_for_message
(void *engine_object, void *_http_message_object);

void ih_net_test_http_engine_destroy(void *engine_object);

void ih_net_test_http_engine_maintain(void *engine_object);

void ih_net_test_http_engine_run(void *engine_thread_object);

void ih_net_test_http_engine_start(void *engine_thread_object);

void ih_net_test_http_engine_stop(void *engine_thread_object);

#endif
