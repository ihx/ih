#ifndef ih_infi_seq_engine_h
#define ih_infi_seq_engine_h

#include "ih/core/engine.h"
#include "ih/net/server/system.h"

struct ih_infi_seq_engine_t;
typedef struct ih_infi_seq_engine_t ih_infi_seq_engine_t;

void *ih_infi_seq_engine_create(ih_net_server_system_t *ih_net_server,
    void *custom_server_object);

void ih_infi_seq_engine_destroy(void *engine_object);

ih_net_server_system_handle_message_f
ih_infi_seq_engine_get_handler_for_message(void *engine_object,
    void *message_object);

void ih_infi_seq_engine_maintain(void *engine_object);

void ih_infi_seq_engine_run(void *engine_thread_object);

void ih_infi_seq_engine_start(void *engine_thread_object);

void ih_infi_seq_engine_stop(void *engine_thread_object);

#endif
